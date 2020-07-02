/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** main.c
*/

#include "my.h"

dlist_t *set_time(dlist_t *mylist)
{
    struct stat fileStat;
    dlist_node_t *tmp = mylist->begin;
    while (tmp != NULL) {
        stat(tmp->name, &fileStat);
        tmp->mdate = fileStat.st_mtime;
        tmp = tmp->next;
    }
    return (mylist);
}

void flags_check(flags_t *check, char c, char **argv, char *opt_err)
{
    char *flags = "lRdrt";
    while (c != -1) {
        switch (c) {
            case 'l':
                check->lpd = 1;
                break;
            case 'R':
                check->R = 1;
                break;
            case 'd':
                check->d = 1;
                break;
            case 'r':
                check->r = 1;
                break;
            case 't':
                check->t = 1;
                break;
        } c = my_getopt(argv, flags, opt_err);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) no_arg();
    else if (argc > 1) {
        flags_t check = {0};
        char *flags = "lRdrt";
        char opt_err = 0, c = my_getopt(argv, flags, &opt_err);
        if ((c == -1 && opt_err == 0) ||
        (c == 't' && my_strlen(argv[2]) == 2 && argc == 2)) {
            struct dirent *Dirent = NULL;
            if (c == 't') only_flag_t();
            else no_flag(argv, Dirent);
        } else
            flags_check(&check, c, argv, &opt_err);
        if (opt_err != 0)
            my_printf("./my_ls: invalid option -- '%c'\nTry './my_ls --help'"
                        " for more information.\n", opt_err, strerror(errno));
        no_flag_no_arg_rev(&check, argc, argv);
        d_flag_switch(&check, argv);
    }
    return (0);
}