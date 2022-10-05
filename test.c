/*
** EPITECH PROJECT, 2022
** Ftrace
** File description:
** Bootstrap
*/

#include <stdlib.h>
#include <stdio.h>
#include <libelf.h>

void toto(void)
{
    printf("i am toto()\n");
}

void tutu(void)
{
    printf("i am tutu()\n");
}

int main(void) {
    toto();
    tutu();
    exit(0);
}