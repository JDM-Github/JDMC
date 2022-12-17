#pragma once

#ifndef __EVAL__H_
#define __EVAL__H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <string>

double eval(const char *__equation);

double __equate(double __fir, double __sec, char __oper)
{
    switch (__oper)
    {
    case '+':
        return (__fir + __sec);
    case '-':
        return (__fir - __sec);
    case '/':
        return (__fir / __sec);
    case '*':
        return (__fir * __sec);
    case '^':
        return pow(__fir, __sec);
    default:
        return 0;
    }
}

int __in_expression(char __f, char *__expression)
{
    int index = 0;
    while (__expression[index] != 0)
        if (__expression[index++] == __f)
            return 1;
    return 0;
}

void __connect_string(char *__main_string, double __eval, int __rindex_f, int __rindex_b, int __len)
{

    char *__first = (char *)calloc(__rindex_b + 1, sizeof(char));
    memcpy(__first, __main_string, sizeof(char) * __rindex_b);

    char *__last = (char *)calloc((__len - __rindex_f) + 1, sizeof(char));
    memcpy(__last, __main_string + __rindex_f, sizeof(char) * (__len - __rindex_f));

    char __evaluation[50];
    snprintf(__evaluation, 50, "%lf", __eval);

    int first_len = strlen(__first);
    int second_len = strlen(__last);
    int third_len = strlen(__evaluation);
    int new_len = first_len + second_len + third_len + 1;

    memcpy(__main_string, __first, sizeof(char) * first_len);
    memcpy(__main_string + first_len, __evaluation, sizeof(char) * third_len);
    memcpy(__main_string + first_len + third_len, __last, sizeof(char) * second_len);
    __main_string[new_len - 1] = 0;

    free(__first);
    free(__last);
}

void __evaluate_string(char *__main_string, char *__express)
{
    int __fis_neg, __sis_neg, __len,
        __flag, __index, __rindex_b, __rindex_f,
        __findx, __sindx, __fstopper, __sstopper;
    char __operator, __character, __first_char[50], __second_char[50];
    double __first_num, __second_num, __evaluation;
    while (1)
    {
        __fis_neg = 0, __sis_neg = 0, __len = strlen(__main_string),
        __flag = 0, __index = 0, __rindex_b = 0, __rindex_f = 0,
        __findx = 0, __sindx = 0, __fstopper = 1, __sstopper = 1;
        __operator = ' ', __character, __first_char[50], __second_char[50];
        __first_num = 0, __second_num = 0, __evaluation = 0.0;

        while (__index < __len)
        {
            __character = __main_string[__index];
            if (!__flag)
            {
                if (__character == '-' && __express[0] == '+' && __index == 0)
                {
                    __index++;
                    continue;
                }
                if (__in_expression(__character, __express))
                {
                    __flag = 1;
                    __operator = __character;
                    int i = 0;
                    char __new_char = ' ';
                    for (i = __index - 1; i >= -1; i--)
                    {
                        if (i > -1)
                        {
                            __new_char = __main_string[i];
                            if (__new_char == '-')
                                if (((i - 1 > -1) && (__in_expression(__main_string[i - 1], "*/+-^"))) || i - 1 <= 0)
                                {
                                    __fis_neg = 1;
                                    continue;
                                }
                        }
                        if (i <= -1 || __in_expression(__new_char, "*/+-^"))
                        {
                            int __new_indx = (__fis_neg) ? i + 1 : i;
                            while (1)
                            {
                                ++__new_indx;
                                __new_char = __main_string[__new_indx];
                                if ((__new_char >= '0' && __new_char <= '9') || __new_char == '.')
                                {
                                    assert(__fstopper && "There is a space between number");
                                    __first_char[__findx++] = __new_char;
                                }
                                else if (__in_expression(__new_char, "*/+-^"))
                                    break;
                                else
                                {
                                    if (isspace(__new_char) && __findx)
                                        __fstopper = 0;
                                    assert(isspace(__new_char) && "Invalid character");
                                }
                            }
                            break;
                        }
                    }
                    __rindex_b = i + 1;
                    if (__main_string[__index + 1] == '-')
                    {
                        __sis_neg = 1;
                        __index += 2;
                        continue;
                    }
                }
            }
            else
            {
                if ((__character >= '0' && __character <= '9') || __character == '.')
                {
                    assert(__sstopper && "There is a space between number");
                    __second_char[__sindx++] = __character;
                }
                else if (__in_expression(__character, "*/+-^"))
                    break;
                else
                {
                    if (isspace(__character) && __sindx)
                        __sstopper = 0;
                    assert(isspace(__character) && "Invalid character");
                }
            }
            __index++;
            if (!(__index < __len))
                break;
        }

        if (__flag)
        {
            __first_char[__findx] = 0;
            sscanf(__first_char, "%lf", &__first_num);
            if (__fis_neg)
                __first_num *= -1;

            __second_char[__sindx] = 0;
            sscanf(__second_char, "%lf", &__second_num);
            if (__sis_neg)
                __second_num *= -1;

            __evaluation = __equate(__first_num, __second_num, __operator);
            __rindex_f = __index;
            __connect_string(__main_string, __evaluation, __rindex_f, __rindex_b, __len);
            continue;
        }
        break;
    }
}

void __check_parenthesis(char *__main_string)
{
    int index, __rindx, __len;
    int __rindex_f, __rindex_b;
    char __character = ' ';
    char __equation[50];
    while (1)
    {
        __len = strlen(__main_string);
        index = __rindx = 0;
        __rindex_f = __rindex_b = -1;
        while (index < __len)
        {
            __character = __main_string[index];
            if (__in_expression(__character, ")]}"))
            {
                assert(__rindex_b != -1 && "No Opening Symbol Found");
                assert(((__main_string[__rindex_b] == '(' && __character == ')') ||
                        (__main_string[__rindex_b] == '[' && __character == ']') ||
                        (__main_string[__rindex_b] == '{' && __character == '}')) &&
                       "Wrong Symbol");
                __rindex_f = index + 1;
                break;
            }
            if (__in_expression(__character, "([{"))
                __rindex_b = index;
            index++;
        }
        if (__rindex_b != -1)
        {
            assert(__rindex_f != -1 && "No Closing Symbol Found");
            for (int i = __rindex_b + 1; i < __rindex_f - 1; i++)
                __equation[__rindx++] = __main_string[i];
            __equation[__rindx] = 0;
            __connect_string(__main_string, eval(__equation), __rindex_f, __rindex_b, __len);
            continue;
        }
        break;
    }
}

double eval(const char *__equation)
{
    double __evaluation = 0.0;
    int __running = 1;
    int __len = strlen(__equation);
    char *__main_string = (char *)calloc(1000, sizeof(char));
    memmove(__main_string, __equation, sizeof(char) * (__len + 1));
    __check_parenthesis(__main_string);
    __evaluate_string(__main_string, "^");
    __evaluate_string(__main_string, "*/");
    __evaluate_string(__main_string, "+-");
    sscanf(__main_string, "%lf", &__evaluation);
    free(__main_string);
    return __evaluation;
}

#endif
