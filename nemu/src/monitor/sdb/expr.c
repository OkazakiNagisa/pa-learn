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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum TokenType
{
    TK_NOTYPE = 256,
    TK_EQ = '=',

    /* TODO: Add more token types */
    TK_ADD = '+',
    TK_MINUS = '-',
    TK_MULTIPLY = '*',
    TK_DIV = '/',
    TK_BRACKET_LEFT = '(',
    TK_BRACKET_RIGHT = ')',
    TK_NUMBER_DEC = 'd',
    TK_NUMBER_HEX = 'x',
    TK_REG = '$',
    TK_DEREFERENCE = '&',
};

static struct rule
{
    const char *regex;
    int token_type;
} rules[] = {
    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */
    {" +", TK_NOTYPE}, // spaces
    {"\\+", '+'},      // plus
    {"==", TK_EQ},     // equal
    {"-", TK_MINUS},
    {"\\*", TK_MULTIPLY},
    {"/", TK_DIV},
    {"\\(", TK_BRACKET_LEFT},
    {"\\)", TK_BRACKET_RIGHT},
    {"[0-9]+", TK_NUMBER_DEC},
    {"0x[0-9a-fA-F]+", TK_NUMBER_HEX},
    {"$[0-9a-fA-F]+", TK_REG},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
    int i;
    char error_msg[128];
    int ret;

    for (i = 0; i < NR_REGEX; i++)
    {
        ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
        if (ret != 0)
        {
            regerror(ret, &re[i], error_msg, 128);
            panic("regex compilation failed: %s\n%s", error_msg,
                  rules[i].regex);
        }
    }
}

typedef struct token
{
    enum TokenType type;
    char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char *e)
{
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = -1;

    while (e[position] != '\0')
    {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i++)
        {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 &&
                pmatch.rm_so == 0)
            {
                char *substr_start = e + position;
                int substr_len = pmatch.rm_eo;

                Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
                    i, rules[i].regex, position, substr_len, substr_len,
                    substr_start);

                position += substr_len;

                /* TODO: Now a new token is recognized with rules[i]. Add codes
                 * to record the token in the array `tokens'. For certain types
                 * of tokens, some extra actions should be performed.
                 */
                if (nr_token >= 31)
                {
                    Log("Token count too long!");
                    break;
                }
                nr_token++;
                tokens[nr_token].type = rules[i].token_type;

                switch (rules[i].token_type)
                {
                case TK_NUMBER_DEC:
                    if (substr_len >= 32)
                    {
                        Log("Token length too long!");
                        break;
                    }
                    memcpy(&tokens[nr_token].str, &e[position - substr_len],
                           substr_len);
                    tokens[nr_token].str[substr_len] = 0;
                    break;
                case TK_NUMBER_HEX:
                case TK_REG:
                    if (substr_len >= 32)
                    {
                        Log("Token length too long!");
                        break;
                    }
                    memcpy(&tokens[nr_token].str + 1,
                           &e[position - substr_len + 1], substr_len - 1);
                    tokens[nr_token].str[substr_len - 1] = 0;
                    break;
                case TK_MULTIPLY:
                    if (nr_token == 0 || 0)
                        tokens[nr_token].type = TK_DEREFERENCE;
                    break;
                case TK_EQ:
                case TK_ADD:
                case TK_MINUS:
                case TK_DIV:
                case TK_BRACKET_LEFT:
                case TK_BRACKET_RIGHT:
                case TK_NOTYPE:
                    break;
                default:
                    panic("???");
                }

                break;
            }
        }

        if (i == NR_REGEX)
        {
            printf("no match at position %d\n%s\n%*.s^\n", position, e,
                   position, "");
            return false;
        }
    }

    return true;
}

typedef struct UintResult
{
    uint32_t result;
    bool succeeded;
} UintResult;

bool check_parenteses(int p, int q)
{
    if (tokens[p].type != TK_BRACKET_LEFT || tokens[q].type != TK_BRACKET_RIGHT)
        return false;

    int stack_pointer = 0;
    for (int i = p + 1; i <= q - 1; i++)
    {
        if (tokens[i].type == TK_BRACKET_LEFT)
            stack_pointer++;

        if (tokens[i].type == TK_BRACKET_RIGHT)
            if (--stack_pointer < 0)
                return false;
    }
    return stack_pointer == 0;
}

UintResult eval(int p, int q)
{
    while (tokens[p].type == TK_NOTYPE)
        p++;
    while (tokens[q].type == TK_NOTYPE)
        q--;

    UintResult ret;
    if (p > q || p > nr_token || q > nr_token)
        panic("????");

    else if (p == q)
    {
        int succ = sscanf(tokens[p].str, "%u", &ret.result);
        ret.succeeded = !!succ;
        return ret;
    }
    else if (check_parenteses(p, q))
        return eval(p + 1, q - 1);
    else
    {
        int split_pos = -1;
        bool split_pos_is_add_min = false;
        int stack_pointer = 0;
        for (int i = p; i <= q; i++)
        {
            // brackets
            if (tokens[i].type == TK_BRACKET_LEFT)
            {
                stack_pointer++;
                continue;
            }
            if (tokens[i].type == TK_BRACKET_RIGHT)
            {
                if (--stack_pointer < 0)
                {
                    ret.succeeded = false;
                    return ret;
                }
                continue;
            }
            if (stack_pointer)
                continue;

            if (tokens[i].type == TK_ADD || tokens[i].type == TK_MINUS)
            {
                split_pos = i;
                split_pos_is_add_min = true;
            }
            if (tokens[i].type == TK_MULTIPLY || tokens[i].type == TK_DIV)
                if (!split_pos_is_add_min)
                    split_pos = i;
        }
        if (split_pos == -1)
        {
            ret.succeeded = false;
            return ret;
        }

        UintResult result_l = eval(p, split_pos - 1);
        UintResult result_r = eval(split_pos + 1, q);
        ret.succeeded = result_l.succeeded && result_r.succeeded;
        if (!ret.succeeded)
            return ret;

        switch (tokens[split_pos].type)
        {
        case TK_ADD:
            ret.result = result_l.result + result_r.result;
            break;
        case TK_MINUS:
            ret.result = result_l.result - result_r.result;
            break;
        case TK_MULTIPLY:
            ret.result = result_l.result * result_r.result;
            break;
        case TK_DIV:
            if (result_r.result == 0)
            {
                ret.succeeded = false;
                return ret;
            }
            ret.result = result_l.result / result_r.result;
            break;
        default:
            panic("???");
        }
        return ret;
    }
}

word_t expr(char *e, bool *success)
{
    if (!make_token(e))
    {
        *success = false;
        return 0;
    }

    /* TODO: Insert codes to evaluate the expression. */
    UintResult result = eval(0, nr_token);

    *success = result.succeeded;
    return result.result;
}
