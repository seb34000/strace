/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** utils_tracing
*/

#include "strace.h"

char *get_syscall_name(long long int orig_rax)
{
    char *unknown = NULL;

    for (int i = 0; i < MAX_SYCALL; i++) {
        if (table[i].code == orig_rax)
            return (table[i].name);
    }
    unknown = malloc(sizeof(char) * UNKNOWN_FUNC_MAX_LEN);
    snprintf(unknown, sizeof(char) * UNKNOWN_FUNC_MAX_LEN, \
    "syscall_0x%llx", orig_rax);
    return (unknown);
}

unsigned long long get_syscall_value(pid_t child, int regs_value)
{
    int size = sizeof(unsigned long long) * regs_value;

    return (ptrace(PTRACE_PEEKUSER, child, size, 0));
}

unsigned long long get_syscall_args(pid_t child, int idx)
{
    int regs[MAX_ARGS];

    regs[0] = RDI;
    regs[1] = RSI;
    regs[2] = RDX;
    regs[3] = R10;
    regs[4] = R8;
    regs[5] = R9;
    return (get_syscall_value(child, regs[idx]));
}