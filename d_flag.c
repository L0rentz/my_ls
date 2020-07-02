/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** d_flag
*/

#include "my.h"

void d_flag_switch(flags_t *check, char **argv)
{
    if (check->d == 1) {
        dlist_t *mylist = d_flag(check, argv);
        if (check->lpd == 0 && check->r == 0)
            print_list(mylist);
        if (check->lpd == 0 && check->r == 1)
            print_list_rev(mylist);
        if (check->lpd == 1 && check->r == 0)
            print_ld(mylist);
        if (check->lpd == 1 && check->r == 1)
            print_ld_rev(mylist);
        free(mylist);
    }
}

void print_ld_no_arg(void)
{
    char buff[100] = {0};
    size_t bufsize = 100;
    readlink(".", buff, bufsize), buff[99] = '\0';
    struct stat fileStat;
    if (buff[0] == '\0') stat(".", &fileStat);
    else lstat(".", &fileStat);
    ternary_land(fileStat);
    my_printf(" %d", fileStat.st_nlink);
    my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
    my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
    my_printf(" %d", fileStat.st_size);
    char *date = ctime(&fileStat.st_mtime);
    date[16] = '\0', date += 4;
    my_printf(" %s", date), my_printf(" .");
    if (buff[0] != '\0') my_printf(" -> %s\n", buff);
    else my_printf("\n");
}

void print_ld_rev(dlist_t *li)
{
    if (is_empty_list(li)) return;
    dlist_node_t *tmp = li->end;
    while (tmp != NULL) {
        char buff[100] = {0};
        size_t bufsize = 100;
        readlink(tmp->name, buff, bufsize), buff[99] = '\0';
        struct stat fileStat;
        if (buff[0] == '\0') stat(tmp->name, &fileStat);
        else lstat(tmp->name, &fileStat);
        ternary_land(fileStat), my_printf(" %d", fileStat.st_nlink);
        my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
        my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
        my_printf(" %d", fileStat.st_size);
        char *date = ctime(&fileStat.st_mtime);
        date[16] = '\0', date += 4;
        my_printf(" %s", date), my_printf(" %s", tmp->name);
        if (buff[0] != '\0') my_printf(" -> %s\n", buff);
        else my_printf("\n");
        tmp = tmp->back;
    }
}

void print_ld(dlist_t *li)
{
    if (is_empty_list(li)) return;
    dlist_node_t *tmp = li->begin;
    while (tmp != NULL) {
        char buff[100] = {0};
        size_t bufsize = 100;
        readlink(tmp->name, buff, bufsize), buff[99] = '\0';
        struct stat fileStat;
        if (buff[0] == '\0') stat(tmp->name, &fileStat);
        else lstat(tmp->name, &fileStat);
        ternary_land(fileStat), my_printf(" %d", fileStat.st_nlink);
        my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
        my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
        my_printf(" %d", fileStat.st_size);
        char *date = ctime(&fileStat.st_mtime);
        date[16] = '\0', date += 4;
        my_printf(" %s", date), my_printf(" %s", tmp->name);
        if (buff[0] != '\0') my_printf(" -> %s\n", buff);
        else my_printf("\n");
        tmp = tmp->next;
    }
}

dlist_t *d_flag(flags_t *check, char **argv)
{
    int count = 0;
    dlist_t *mylist = new_list();
    for (int i = 1; argv[i] != NULL; i++)
        if (argv[i][0] != '-') count++;
    for (int i = 1; argv[i] != NULL; i++) {
        for (; argv[i] != NULL && argv[i][0] == '-' ; i++);
        if (argv[i] == NULL && count != 0) break;
        errno = 0;
        DIR *Dir = NULL;
        if (argv[i] != NULL) Dir = opendir(argv[i]);
        if (errno != ENOENT && count != 0)
            mylist = push_back_list(mylist, argv[i]);
        if (Dir == NULL && check->lpd == 0 && count == 0) { my_printf(".\n");
            break;
        } else if (Dir == NULL && check->lpd == 1 && count == 0) {
            print_ld_no_arg();
            break;
        } if (errno == ENOENT) my_printf("./my_ls: cannot access '%s': %s\n",
            argv[i], strerror(errno)), exit(84);
    } return (mylist);
}