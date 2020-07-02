/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** l_flag2
*/

#include "my.h"

void rev_l(char *argv, int *count, int nb)
{
    static int check_file = 0;
    errno = 0;
    DIR *Dir;
    Dir = opendir(argv);
    if (errno != ENOENT) {
        if (Dir == NULL) {
            print_l_file(argv);
            check_file = 1;
        }
        rev_l_2(argv, check_file, Dir, nb);
        if (Dir != NULL)
            check_file = 0;
        if (*count < nb - 1 && Dir != NULL)
            my_printf("\n");
    } else if (Dir == NULL && errno != ENOTDIR) {
        my_printf("./my_ls: cannot access '%s': %s\n", argv, strerror(errno));
        exit(84);
    }
    *count += 1;
}

void rev_l_2(char *argv, int check_file, DIR *Dir, int nb)
{
    if (Dir != NULL) {
        dlist_t *mylist = new_list();
        struct dirent *Dirent;
        while ((Dirent = readdir(Dir)) != NULL) {
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        } if (check_file == 1)
            my_printf("\n");
        if (nb != 1)
            my_printf("%s:\n", argv);
        if (mylist != NULL)
            my_printf("total %d\n", blocks_calcul_multi(mylist, argv));
        print_lflag_rev(mylist, argv);
        mylist = clear_list(mylist), closedir(Dir);
    }
}

void no_rev_l(char *argv, int *count, int nb)
{
    static int check_file = 0;
    errno = 0;
    DIR *Dir;
    Dir = opendir(argv);
    if (errno != ENOENT) {
        if (Dir == NULL) {
            print_l_file(argv);
            check_file = 1;
        }
        no_rev_l_2(argv, check_file, Dir, nb);
        if (Dir != NULL)
            check_file = 0;
        if (*count < nb - 1 && Dir != NULL && nb != 1)
            my_printf("\n");
    } else if (Dir == NULL && errno != ENOTDIR) {
        my_printf("./my_ls: cannot access '%s': %s\n", argv, strerror(errno));
        exit(84);
    }
    *count += 1;
}

void no_rev_l_2(char *argv, int check_file, DIR *Dir, int nb)
{
    if (Dir != NULL) {
        dlist_t *mylist = new_list();
        struct dirent *Dirent;
        while ((Dirent = readdir(Dir)) != NULL) {
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        } if (check_file == 1)
            my_printf("\n");
        if (nb != 1)
            my_printf("%s:\n", argv);
        if (mylist != NULL)
            my_printf("total %d\n", blocks_calcul_multi(mylist, argv));
        print_lflag(mylist, argv);
        mylist = clear_list(mylist), closedir(Dir);
    }
}

void l_flag(flags_t *check, char **argv, int argc)
{
    int nb = 0;
    for (int i = 1; argv[i] != NULL; i++)
        if (argv[i][0] != '-')
            nb++;
    for (int i = 1, count = 0; check->r == 0 && argv[i] != NULL; i++) {
        if (argv[i][0] != '-' && check->t == 0)
            no_rev_l(argv[i], &count, nb);
        else if (argv[i][0] != '-' && check->t == 1)
            no_rev_l_time(argv[i], &count, nb);
    }
    for (int i = argc - 1, count = 0; check->r == 1 && i != 0; i--) {
        if (argv[i][0] != '-' && check->t == 0)
            rev_l(argv[i], &count, nb);
        else if (argv[i][0] != '-' && check->t == 1)
            rev_l_time(argv[i], &count, nb);
    }
}