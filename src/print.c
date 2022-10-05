/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** print
*/

#include "strace.h"

char *get_string(pid_t child, unsigned long long addr)
{
    size_t alloc = 4096;
    char *str = malloc(sizeof(char) * alloc);
    long *read_addr = (long *)addr;
    long *cpy_addr = (long *)str;
    size_t read_bytes = 0;
    size_t ret = 0;

    if (addr == 0x0) {
        str = "NULL";
        return (str);
    }
    memset(str, '\0', alloc);
    do {
        ret = ptrace(PTRACE_PEEKTEXT, child, read_addr++, NULL);
        *(cpy_addr++) = ret;
        read_bytes += sizeof(long);
    } while (ret && read_bytes < (alloc - sizeof(long)));
    return (str);
}

void display_args_name(tracing_t *trace, int call_idx, int arg_idx, int nb_arg)
{
    unsigned long long value = get_syscall_args(trace->child, arg_idx);
    char *tmp;

    if (table[call_idx].args[arg_idx] == NUM) {
        printf(arg_idx == 0 ? "%lld" : " %lld", value);
        arg_idx + 1 != nb_arg ? printf(",") : 0;
    } else if (table[call_idx].args[arg_idx] == STRING) {
        tmp = get_string(trace->child, value);
        printf(arg_idx == 0 ? "\"%s\"" : " \"%s\"", tmp);
        arg_idx + 1 != nb_arg ? printf(",") : 0;
    } else {
        printf(arg_idx == 0 ? "0x%llx" : " 0x%llx", value);
        arg_idx + 1 != nb_arg ? printf(",") : 0;
    }
}

void display_args(char *syscall_name, tracing_t *trace)
{
    int nb_args = MAX_ARGS;
    int syscall_idx = 0;
    int args_idx = 0;
    unsigned long long args = 0;

    for (; syscall_idx < MAX_SYCALL; syscall_idx++) {
        if (strncmp(table[syscall_idx].name, syscall_name, \
        strlen(syscall_name)) == 0) {
            nb_args = table[syscall_idx].nbArgs;
            break;
        }
    }
    for (; args_idx < nb_args; args_idx++) {
        if (trace->isS) {
            display_args_name(trace, syscall_idx, args_idx, nb_args);
        } else {
            args = get_syscall_args(trace->child, args_idx);
            printf(args_idx == 0 ? "0x%llx" : " 0x%llx", args);
            args_idx + 1 != nb_args ? printf(",") : 0;
        }
    }
}

void display_return_value(tracing_t *trace)
{
    if (trace->isS && table[trace->regs.orig_rax].returnType == NUM)
        printf(trace->regs.rax ? "%lld\n" : "0x0\n", trace->regs.rax);
    else
        printf(trace->regs.rax ? "0x%llx\n" : "0x0\n", trace->regs.rax);
}

void display_all(tracing_t *trace)
{
    char *syscall_name;

    if (trace->regs.orig_rax <= MAX_SYCALL) {
        syscall_name = get_syscall_name(trace->regs.orig_rax);
        printf("%s(", syscall_name);
        display_args(syscall_name, trace);
        printf(")\t\t= ");
        display_return_value(trace);
    }
}