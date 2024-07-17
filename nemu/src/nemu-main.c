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

#include <common.h>
#include "monitor/sdb/sdb.h"

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[])
{
    if (argc == 3 && !strcmp(argv[1], "xx"))
    {
        void init_regex();
        init_regex();
        FILE *f = fopen(argv[2], "r");
        assert(f);
        // int size = ftell(f);
        // rewind(f);
        // char *buf = calloc(1, size);
        // assert(buf);
        // fread(buf, size, 1, f);
        uint32_t expected;
        char expression[65536] = {0};
        while (fscanf(f, "%u %[^\n]", &expected, expression) > 0)
        {
            getc(f);
            bool succ;
            int result = expr(expression, &succ);
            if (!succ)
                printf("expr: %s, expected: %u, calc: failed\n", expression,
                       expected);
            else if (result != expected)
                printf("expr: %s, expected: %u, calc: %u\n", expression,
                       expected, result);
            else
                printf("expr good\n");
        }
        fclose(f);
        return 0;
    }
    /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
    am_init_monitor();
#else
    init_monitor(argc, argv);
#endif

    /* Start engine. */
    engine_start();

    return is_exit_status_bad();
}
