/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** get_args
*/

#include "strace.h"

args_t *init_args(void)
{
    args_t *args = malloc(sizeof(args_t));

    args->args = NULL;
    args->pid = -1;
    args->isPid = false;
    args->detailPrint = false;
    return (args);
}

void get_args_pid(args_t *args, int ac, char **av, int i)
{
    char err[64] = "Invalid process id: ";

    if (i + 1 >= ac) {
        free(args);
        put_error("option requires an argument -- 'p'", true);
    }
    if (i + 1 < ac && str_is_num(av[i + 1])) {
        args->pid = atoi(av[i + 1]);
        args->isPid = true;
    } else {
        strcat(err, av[i + 1]);
        free(args);
        put_error(err, false);
    }
}

args_t *get_args_name(args_t *args, int ac, char **av, int i)
{
    char err[64] = "Can't stat '";

    if (access(av[i], F_OK) == 0) {
        args->args = malloc(sizeof(char *) * ac);
        for (int j = 0; i < ac; i++, j++)
            args->args[j] = strdup(av[i]);
        return (args);
    } else {
        free(args);
        strcat(err, av[i]);
        strcat(err, "': No such file or directory");
        put_error(err, false);
    }
    return (NULL);
}

args_t *get_args(int ac, char **av)
{
    args_t *args = init_args();
    bool pidLaunch = false;

    for (int i = 0; i < ac; i++) {
        if (strncmp(av[i], "-p", 2) == 0) {
            get_args_pid(args, ac, av, i);
            pidLaunch = true;
        } else if (strncmp(av[i], "-s", 2) == 0)
            args->detailPrint = true;
    }
    for (int i = 1; i < ac && !pidLaunch; i++) {
        if (av[i][0] != '-') {
            get_args_name(args, ac, av, i);
            break;
        }
    }
    return (args);
}