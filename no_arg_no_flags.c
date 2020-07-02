/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** no_arg_no_flags
*/

#include "my.h"

void no_arg(void)
{
    struct dirent *Dirent;
    DIR *Dir;
    Dir = opendir(".");
    dlist_t *mylist = new_list();
    while ((Dirent = readdir(Dir)) != NULL) {
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    }
    closedir(Dir);
    print_list(mylist);
    clear_list(mylist);
}

void no_arg_rev(void)
{
    struct dirent *Dirent;
    DIR *Dir;
    Dir = opendir(".");
    dlist_t *mylist = new_list();
    while ((Dirent = readdir(Dir)) != NULL) {
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    }
    closedir(Dir);
    print_list_rev(mylist);
    clear_list(mylist);
}

void only_flag_t(void)
{
    struct dirent *Dirent;
    DIR *Dir;
    Dir = opendir(".");
    dlist_t *mylist = new_list();
    while ((Dirent = readdir(Dir)) != NULL) {
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    }
    mylist = set_time(mylist);
    mylist = sort_modif_time(mylist);
    closedir(Dir);
    print_list(mylist);
    clear_list(mylist);
}

void no_flag(char **argv, struct dirent *Dirent)
{
    for (int i = 1, check = 0; argv[i] != NULL; i++) {
        for (; argv[i] != NULL && argv[i][0] == '-'; i++);
        if (argv[i] == NULL) break;
        dlist_t *mylist = new_list();
        DIR *Dir = opendir(argv[i]);
        if (Dir == NULL && errno == ENOTDIR)
            my_printf("%s\n", argv[i]), check = 1;
        else if (Dir == NULL && errno != ENOTDIR) {
            my_printf("./my_ls: cannot access '%s': %s\n",
                argv[i], strerror(errno)), exit(84);
        } while ((errno != ENOTDIR && (Dirent = readdir(Dir)) != NULL))
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        if (check == 1 && Dir != NULL) {
            my_printf("\n"), check = 0;
        } if (argv[2] != NULL && argv[i] != NULL && errno != ENOTDIR) {
            my_printf("%s:\n", argv[i]), print_list(mylist);
            if (argv[i + 1] != NULL) my_printf("\n");
        } else print_list(mylist);
        closedir(Dir), clear_list(mylist); }
}

void no_flag_no_arg_rev(flags_t *check, int argc, char **argv)
{
    if (check->lpd == 1 && check->R == 0 && check->d == 0
        && check->t == 0 && argc == 2) { l_flag_no_arg(check);
        return;
    } else if (check->lpd == 1 && check->R == 0 && check->d == 0 && argc > 2) {
        l_flag(check, argv, argc);
        return;
    } if (check->lpd == 0 && check->R == 0 && check->d == 0
        && check->r == 1 && check->t == 0 && argc == 2) { no_arg_rev();
        return;
    } else  if (check->lpd == 0 && check->R == 0 && check->d == 0
                && check->r == 1 && check->t == 0 && argc > 2) {
        no_flag_rev(argv, argc);
        return;
    } if (check->R == 0 && check->d == 0 && check->t == 1 && argc == 2) {
        t_flag_no_arg(check);
        return;
    } if (check->R == 0 && check->d == 0 && check->t == 1 && check->lpd == 0
        && check->r == 0) t_flag_args(argv);
    else if (check->R == 0 && check->d == 0 && check->t == 1 && check->lpd == 0
        && check->r == 1) t_flag_args_rev(argv, argc);
}