/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** error
*/

#include "strace.h"

void put_error(char const *error, bool printHelp)
{
    fprintf(stderr, "strace: %s\n", error);
    if (printHelp)
        fprintf(stderr, "Try 'strace -h' for more information.\n");
    exit(84);
}