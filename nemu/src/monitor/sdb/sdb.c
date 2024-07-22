/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <memory/paddr.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin.
 */
static char *rl_gets()
{
    static char *line_read = NULL;

    if (line_read)
    {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("(nemu) ");

    if (line_read && *line_read)
    {
        add_history(line_read);
    }

    return line_read;
}

static int cmd_c(char *args)
{
    cpu_exec(-1);
    return 0;
}

static int cmd_q(char *args)
{
    return -1;
}

static int cmd_si(char *args)
{
    if (args && strlen(args) != 0)
    {
        word_t n;
        if (sscanf(args, "%d", &n) == 1)
            cpu_exec(n);
        else
            Log("Bad paramater");
    }
    else
    {
        cpu_exec(1);
    }
    return 0;
}

static int cmd_info(char *args)
{
    if (!strcmp(args, "r"))
    {
        isa_reg_display();
    }
    else if (!strcmp(args, "w"))
    {
        list_watchpoints();
    }
    else
    {
        Log("Unknown subcommand");
    }
    return 0;
}

inline static void hex_dump(paddr_t data, int size)
{
    int i, offset;
    for (offset = 0; offset < size; offset += 16)
    {
        // print addr
        printf("%08x  ", data + offset);
        // print hex
        for (i = 0; i < 16; i++)
        {
            if (i % 8 == 0)
                putchar(' ');

            if (offset + i < size)
                printf("%02x ", guest_to_host(data)[offset + i]);
            else
                printf("   ");
        }
        printf("   ");
        // print ascii
        for (i = 0; i < 16 && offset + i < size; i++)
        {
            if (isprint(guest_to_host(data)[offset + i]))
                printf("%c", guest_to_host(data)[offset + i]);
            else
                putchar('.');
        }
        putchar('\n');
    }
}

static int cmd_x(char *args)
{
    word_t n;
    paddr_t expr;
    if (sscanf(args, "%d %x", &n, &expr) == 2)
    {
        hex_dump(expr, n);
    }
    return 0;
}

int cmd_p(char *args)
{
    bool succeeded;
    word_t result = expr(args, &succeeded);
    if (succeeded)
        printf("eval: %u (0x%x)\n", result, result);
    else
        printf("eval failed.\n");
    return 0;
}

int cmd_w(char *args)
{
    new_wp(args);
    return 0;
}

int cmd_d(char *args)
{
    int no;
    if (sscanf(args, "%d", &no) == 1)
        free_wp_no(no);
    return 0;
}

static int cmd_help(char *args);

static struct
{
    const char *name;
    const char *description;
    int (*handler)(char *);
} cmd_table[] = {
    {"help", "Display information about all supported commands", cmd_help},
    {"c", "Continue the execution of the program", cmd_c},
    {"q", "Exit NEMU", cmd_q},

    /* TODO: Add more commands */
    {"si", "Step N", cmd_si},
    {"info", "Show info", cmd_info},
    {"x", "Show memory", cmd_x},
    {"p", "Eval", cmd_p},
    {"w", "Set watchpoint", cmd_w},
    {"d", "Delete watchpoint", cmd_d},
};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args)
{
    /* extract the first argument */
    char *arg = strtok(NULL, " ");
    int i;

    if (arg == NULL)
    {
        /* no argument given */
        for (i = 0; i < NR_CMD; i++)
        {
            printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        }
    }
    else
    {
        for (i = 0; i < NR_CMD; i++)
        {
            if (strcmp(arg, cmd_table[i].name) == 0)
            {
                printf("%s - %s\n", cmd_table[i].name,
                       cmd_table[i].description);
                return 0;
            }
        }
        printf("Unknown command '%s'\n", arg);
    }
    return 0;
}

void sdb_set_batch_mode()
{
    is_batch_mode = true;
}

void sdb_mainloop()
{
    if (is_batch_mode)
    {
        cmd_c(NULL);
        return;
    }

    for (char *str; (str = rl_gets()) != NULL;)
    {
        char *str_end = str + strlen(str);

        /* extract the first token as the command */
        char *cmd = strtok(str, " ");
        if (cmd == NULL)
        {
            continue;
        }

        /* treat the remaining string as the arguments,
         * which may need further parsing
         */
        char *args = cmd + strlen(cmd) + 1;
        if (args >= str_end)
        {
            args = NULL;
        }

#ifdef CONFIG_DEVICE
        extern void sdl_clear_event_queue();
        sdl_clear_event_queue();
#endif

        int i;
        for (i = 0; i < NR_CMD; i++)
        {
            if (strcmp(cmd, cmd_table[i].name) == 0)
            {
                if (cmd_table[i].handler(args) < 0)
                {
                    return;
                }
                break;
            }
        }

        if (i == NR_CMD)
        {
            printf("Unknown command '%s'\n", cmd);
        }
    }
}

void init_sdb()
{
    /* Compile the regular expressions. */
    init_regex();

    /* Initialize the watchpoint pool. */
    init_wp_pool();
}
