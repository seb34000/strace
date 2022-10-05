/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** strace
*/

#ifndef STRACE_H_
#define STRACE_H_

    #include "syscall.h"
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/syscall.h>
    #include <unistd.h>
    #include <sys/ptrace.h>
    #include <sys/user.h>
    #include <sys/reg.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <errno.h>
    #include <ctype.h>
    #include <stdbool.h>

    #define MAX_SYCALL 328
    #define SYSCALL_OPCODE 0x050f
    #define UNKNOWN_FUNC_MAX_LEN 64
    #define MAX_ARGS 6

typedef struct args_s {
    int pid;
    char **args;
    bool isPid;
    bool detailPrint;
} args_t;

typedef struct tracing_s {
    pid_t child;
    bool isS;
    struct user_regs_struct regs;
} tracing_t;

/* UTILS TRACING */
char *get_syscall_name(long long int orig_rax);
unsigned long long get_syscall_value(pid_t child, int regs_value);
unsigned long long get_syscall_args(pid_t child, int idx);

/* STRACE */
int exec_strace(args_t *args);

/* DISPLAY */
void display_all(tracing_t *trace);

/* ERROR */
void put_error(char const *error, bool printHelp);

/* ARGS */
args_t *get_args(int ac, char **av);

/* UTILS */
bool str_is_num(const char *str);

#endif /* !STRACE_H_ */
