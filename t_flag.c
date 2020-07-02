/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** t_flag
*/

#include "my.h"

dlist_t *sort_modif_time(dlist_t *mylist)
{
    int count = 0;
    while (mylist != NULL && errno != ENOTDIR && count != 1) {
        dlist_node_t *tmp = mylist->begin;
        count = 0;
        while (tmp->next != NULL) {
            if (tmp->mdate < tmp->next->mdate) {
                count++;
                char *str = tmp->name;
                tmp->name = tmp->next->name;
                tmp->next->name = str;
                time_t i = tmp->mdate;
                tmp->mdate = tmp->next->mdate;
                tmp->next->mdate = i;
            }
            tmp = tmp->next;
        }
        count++;
    }
    return (mylist);
}

dlist_t *set_time_ar(dlist_t *mylist, char *argv)
{
    struct stat fileStat;
    dlist_node_t *tmp = NULL;
    if (mylist != NULL)
        tmp = mylist->begin;
    while (tmp != NULL) {
        char *str = malloc(sizeof(char) * my_strlen(argv)
            + my_strlen(tmp->name) + 2);
        str[0] = '\0';
        str = my_strcat(str, argv), str = my_strcat(str, "/");
        str = my_strcat(str, tmp->name);
        stat(str, &fileStat);
        tmp->mdate = fileStat.st_mtime;
        tmp = tmp->next;
        free(str);
    }
    return (mylist);
}

void t_flag_no_arg(flags_t *check)
{
    struct dirent *Dirent;
    DIR *Dir;
    Dir = opendir(".");
    dlist_t *mylist = new_list();
    while ((Dirent = readdir(Dir)) != NULL) {
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    } mylist = set_time(mylist);
    mylist = sort_modif_time(mylist);
    closedir(Dir);
    if (check->lpd == 0 && check->r == 0)
        print_list(mylist);
    else if (check->lpd == 0 && check->r == 1)
        print_list_rev(mylist);
    if (check->lpd == 1 && check->r == 0)
        print_list_lflag(mylist);
    else if (check->lpd == 1 && check->r == 1)
        print_lflag_rev(mylist, ".");
    clear_list(mylist);
}

void t_flag_args(char **argv)
{
    struct dirent *Dirent;
    for (int i = 1, check = 0; argv[i] != NULL; i++) {
        for (; argv[i] != NULL && argv[i][0] == '-'; i++);
        if (argv[i] == NULL) break;
        dlist_t *mylist = new_list();
        DIR *Dir = opendir(argv[i]);
        if (Dir == NULL && errno == ENOTDIR)
            my_printf("%s\n", argv[i]), check = 1;
        else if (Dir == NULL && errno != ENOTDIR) exit(84);
        while ((errno != ENOTDIR && (Dirent = readdir(Dir)) != NULL))
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        mylist = set_time_ar(mylist, argv[i]), mylist = sort_modif_time(mylist);
        if (check == 1 && Dir != NULL) {
            my_printf("\n"), check = 0;
        } if (argv[3] != NULL && argv[i] != NULL && errno != ENOTDIR) {
            my_printf("%s:\n", argv[i]), print_list(mylist);
            if (argv[i + 1] != NULL && argv[3] != NULL) my_printf("\n");
        } else print_list(mylist);
        closedir(Dir), clear_list(mylist); }
}

void t_flag_args_rev(char **argv, int argc)
{
    struct dirent *Dirent;
    for (int i = argc - 1, check = 0; i != 1; i--) {
        for (; i != 1 && argv[i][0] == '-'; i--);
        if (i == 0) break;
        dlist_t *mylist = new_list();
        DIR *Dir = opendir(argv[i]);
        if (Dir == NULL && errno == ENOTDIR)
            my_printf("%s\n", argv[i]), check = 1;
        else if (Dir == NULL && errno != ENOTDIR) exit(84);
        while ((errno != ENOTDIR && (Dirent = readdir(Dir)) != NULL))
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        mylist = set_time_ar(mylist, argv[i]), mylist = sort_modif_time(mylist);
        if (check == 1 && Dir != NULL) {
            my_printf("\n"), check = 0;
        } if (argv[3] != NULL && argv[i] != NULL && errno != ENOTDIR) {
            my_printf("%s:\n", argv[i]), print_list_rev(mylist);
            if (i - 1 != 1 && argv[3] != NULL) my_printf("\n");
        } else print_list(mylist);
        closedir(Dir), clear_list(mylist); }
}
