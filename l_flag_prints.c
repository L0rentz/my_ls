/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** l_flag_prints
*/

#include "my.h"

int blocks_calcul(dlist_t *mylist)
{
    char *str = NULL;
    struct stat fileStat;
    int blocks = 0;
    dlist_node_t *tmp = mylist->begin;
    while (tmp != NULL) {
        str = malloc(sizeof(char) * my_strlen(tmp->name) + 1);
        str[0] = '\0';
        str = my_strcat(str, tmp->name);
        stat(str, &fileStat);
        blocks += fileStat.st_blocks;
        tmp = tmp->next;
        free(str);
    }
    blocks /= 2;
    return (blocks);
}

int blocks_calcul_multi(dlist_t *mylist, char *argv)
{
    char *str = NULL;
    struct stat fileStat;
    int blocks = 0;
    dlist_node_t *tmp = mylist->begin;
    while (tmp != NULL) {
        str = malloc(sizeof(char) * my_strlen(argv) + my_strlen(tmp->name) + 2);
        str[0] = '\0';
        str = my_strcat(str, argv), str = my_strcat(str, "/");
        str = my_strcat(str, tmp->name);
        stat(str, &fileStat);
        blocks += fileStat.st_blocks;
        tmp = tmp->next;
        free(str);
    }
    blocks /= 2;
    return (blocks);
}

void print_rights_dot(dlist_node_t *tmp, struct stat fileStat, dlist_t *li)
{
    char *str = malloc(sizeof(char) * my_strlen(tmp->name) + 1);
    static int check = 0;
    str[0] = '\0', str = my_strcat(str, tmp->name);
    char buff[100] = {0};
    size_t bufsize = 100;
    readlink(str, buff, bufsize), buff[99] = '\0';
    if (buff[0] == '\0') stat(str, &fileStat);
    else lstat(str, &fileStat);
    char *date = ctime(&fileStat.st_mtime);
    if (check == 0)
        my_printf("total %d\n", blocks_calcul(li)), check = 1;
    ternary_land(fileStat), my_printf(" %d", fileStat.st_nlink);
    my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
    my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
    if ((fileStat.st_rdev) != 0) { my_printf(" %d,", fileStat.st_rdev/256);
    my_printf(" %d", (fileStat.st_rdev % 256));
    } else my_printf(" %d", fileStat.st_size), date[16] = '\0', date += 4;
    my_printf(" %s", date), my_printf(" %s", tmp->name);
    if (buff[0] != '\0') my_printf(" -> %s\n", buff), free(str);
    else my_printf("\n"), free(str);
}

void print_lflag(dlist_t *li, char *argv)
{
    struct stat fileStat;
    if (is_empty_list(li)) {
        my_printf("total 0\n");
        return;
    }
    dlist_node_t *tmp = li->begin;
    while (tmp != NULL) {
        print_rights(tmp->name, argv, fileStat);
        tmp = tmp->next;
    }
}

void print_lflag_rev(dlist_t *li, char *argv)
{
    struct stat fileStat;
    if (is_empty_list(li)) {
        my_printf("total 0\n");
        return;
    }
    dlist_node_t *tmp = li->end;
    while (tmp != NULL) {
        print_rights(tmp->name, argv, fileStat);
        tmp = tmp->back;
    }
}