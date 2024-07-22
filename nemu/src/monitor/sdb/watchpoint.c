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

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool()
{
    int i;
    for (i = 0; i < NR_WP; i++)
    {
        wp_pool[i].NO = i;
        wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
        wp_pool[i].enabled = false;
        wp_pool[i].expr = NULL;
        wp_pool[i].result = 0;
        wp_pool[i].result_succeeded = false;
    }

    head = NULL;
    free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP *new_wp(const char *expression)
{
    WP *cur = free_;
    if (!cur)
        return cur;
    char *buf = malloc(strlen(expression) + 1);
    if (!buf)
        return NULL;
    free_ = cur->next;
    cur->next = head;
    head = cur;
    cur->enabled = true;
    strcpy(buf, expression);
    cur->expr = buf;
    cur->result = expr(buf, &cur->result_succeeded);
    return cur;
}

void free_wp(WP *wp)
{
    if (!wp)
        return;
    if (wp == head)
        head = wp->next;
    else
    {
        WP *prev = head;
        while (prev && prev->next != wp)
            prev = prev->next;
        if (!prev)
            return;
        prev->next = wp->next;
    }

    assert(wp->enabled && !!wp->expr);
    wp->enabled = false;
    free(wp->expr);

    wp->next = free_;
    free_ = wp;
}

void free_wp_no(int no)
{
    WP *cur = head;
    while (cur && cur->NO != no)
        cur = cur->next;
    if (cur)
        free_wp(cur);
}

void list_watchpoints()
{
    WP *cur = head;
    while (cur)
    {
        printf("%d: %s = ", cur->NO, cur->expr);
        if (cur->result_succeeded)
            printf("%u\n", cur->result);
        else
            printf("(eval failed)\n");
        cur = cur->next;
    }
    return;
}

bool traverse_watchpoints()
{
    bool ret = false;
    WP *cur = head;
    while (cur)
    {
        word_t previous_result = cur->result;
        cur->result = expr(cur->expr, &cur->result_succeeded);
        if (previous_result != cur->result)
        {
            ret |= previous_result != cur->result;
            printf("Watchpoint #%d hit! %s = %u (prev %u)\n", cur->NO,
                   cur->expr, cur->result, previous_result);
        }
        cur = cur->next;
    }
    return ret;
}