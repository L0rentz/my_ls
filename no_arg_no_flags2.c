/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** no_arg_no_flags2
*/

#include "my.h"

void no_flag_rev2(char **argv, int *check, DIR *Dir, int i)
{
    struct dirent *Dirent;
    dlist_t *mylist = new_list();
    while ((errno != ENOTDIR && (Dirent = readdir(Dir)) != NULL))
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    if (*check == 1 && Dir != NULL) {
        my_printf("\n");
        *check = 0;
    } if (argv[2] != NULL && argv[i] != NULL && errno != ENOTDIR) {
        my_printf("%s:\n", argv[i]);
        print_list_rev(mylist);
        if (i > 1)
            my_printf("\n");
    } else
        print_list_rev(mylist);
    closedir(Dir), clear_list(mylist);
}

void no_flag_rev(char **argv, int argc)
{
    for (int i = argc - 1, check = 0; i != 0; i--) {
        for (; i != 0 && argv[i][0] == '-' ; i--);
        if (i == 0) break;
        errno = 0;
        DIR *Dir = opendir(argv[i]);
        if (Dir == NULL && errno == ENOTDIR)
            my_printf("%s\n", argv[i]), check = 1;
        else if (Dir == NULL && errno != ENOTDIR)
            my_printf("./my_ls: cannot access '%s': %s\n",
                        argv[i], strerror(errno)), exit(84);
        no_flag_rev2(argv, &check, Dir, i);
    }
}