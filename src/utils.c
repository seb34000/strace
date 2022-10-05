/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** utils
*/

#include "strace.h"

bool str_is_num(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]))
            return (false);
    }
    return (true);
}
