/*
** EPITECH PROJECT, 2022
** B-PSU-402-MPL-4-1-strace-sebastien.phelip
** File description:
** strace
*/

#include "strace.h"

int handle_loop(int status)
{
    return ((WSTOPSIG(status) == SIGTRAP || WSTOPSIG(status) == SIGSTOP)
    && WIFSTOPPED(status));
}

int launch_child(args_t *args)
{
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
        perror("strace: ptrace");
        return (-1);
    }
    kill(getpid(), SIGSTOP);
    if (execvp(args->args[0], &args->args[0]) == -1) {
        perror("strace execvp:");
        return (-1);
    }
    return (0);

}

void launch_parent(tracing_t *trace)
{
    int status;
    unsigned short syscall;

    waitpid(trace->child, &status, 0);
    while (handle_loop(status)) {
        ptrace(PTRACE_GETREGS, trace->child, NULL, &trace->regs);
        syscall = ptrace(PTRACE_PEEKTEXT, trace->child, trace->regs.rip, NULL);
        ptrace(PTRACE_SINGLESTEP, trace->child, NULL, NULL);
        waitpid(trace->child, &status, 0);
        ptrace(PTRACE_GETREGS, trace->child, NULL, &trace->regs);
        if (syscall == SYSCALL_OPCODE)
            display_all(trace);
    }
    if (trace->isS)
        printf("exit_group(%d)\n", WEXITSTATUS(status));
    else
        printf("exit_group(0x%x)\n", WEXITSTATUS(status));
    printf("+++ exited with %d +++\n", WEXITSTATUS(status));
}

void init_tracing(pid_t child, args_t *args, tracing_t *trace)
{
    trace->child = child;
    trace->isS = args->detailPrint;
}

int exec_strace(args_t *args)
{
    pid_t pid = fork();
    tracing_t trace;

    init_tracing(pid, args, &trace);
    if (pid == -1) {
        perror("strace: fork");
        exit(84);
    } else if (pid == 0) {
        launch_child(args);
    } else {
        launch_parent(&trace);
    }
    return (0);
}