/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** main
*/

#include "strace.h"

void get_help(void)
{
    printf("strace: must have PROG [ARGS] or -p PID\n");
    printf("Try 'strace -h' for more information.\n");
    printf("Usage: strace [-s] [-p <pid>|<command>]\n");
    printf("  -s\t\tprint the system calls in a more detailed way\n");
    printf("  -p <pid>\tattach to the process with the given pid\n");
    printf("  -h\t\tprint the help\n");
}

int main(int ac, char **av)
{
    args_t *args = NULL;

    if (ac == 1) {
        get_help();
        exit(84);
    }
    args = get_args(ac, av);
    exec_strace(args);
    return (0);
}