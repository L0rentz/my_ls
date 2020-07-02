/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** l_flag
*/

#include "my.h"

void ternary_land(struct stat fileStat)
{
    my_printf((S_ISREG(fileStat.st_mode)) ? "-" : "\0");
    my_printf((S_ISDIR(fileStat.st_mode)) ? "d" : "");
    my_printf((S_ISCHR(fileStat.st_mode)) ? "c" : "");
    my_printf((S_ISBLK(fileStat.st_mode)) ? "b" : "");
    my_printf((S_ISFIFO(fileStat.st_mode)) ? "p" : "");
    my_printf((S_ISLNK(fileStat.st_mode)) ? "l" : "");
    my_printf((S_ISSOCK(fileStat.st_mode)) ? "s" : "");
    my_printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    my_printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    my_printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    my_printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    my_printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    my_printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    my_printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    my_printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    if (fileStat.st_mode & S_ISVTX) my_printf("T");
    else my_printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

void print_list_lflag(dlist_t *li)
{
    struct stat fileStat;
    if (is_empty_list(li)) {
        my_printf("total 0\n");
        return;
    }
    dlist_node_t *tmp = li->begin;
    while (tmp != NULL) {
        print_rights_dot(tmp, fileStat, li);
        tmp = tmp->next;
    }
}

void print_list_lflag_rev(dlist_t *li)
{
    struct stat fileStat;
    if (is_empty_list(li)) {
        my_printf("total 0\n");
        return;
    }
    dlist_node_t *tmp = li->end;
    while (tmp != NULL) {
        print_rights_dot(tmp, fileStat, li);
        tmp = tmp->back;
    }
}

void l_flag_no_arg(flags_t *check)
{
    DIR *Dir = opendir(".");
    struct dirent *Dirent;
    dlist_t *mylist = new_list();
    while ((Dirent = readdir(Dir)) != NULL) {
        if (Dirent->d_name[0] != '.')
            mylist = push_back_list(mylist, Dirent->d_name);
    }
    if (check->r == 0)
        print_list_lflag(mylist);
    else if (check->r == 1)
        print_list_lflag_rev(mylist);
    clear_list(mylist), closedir(Dir);
}

void print_rights(char *tmp, char *argv, struct stat fileStat)
{
    char *str = malloc(sizeof(char) * my_strlen(argv) + my_strlen(tmp) + 2);
    str[0] = '\0';
    str = my_strcat(str, argv), str = my_strcat(str, "/");
    str = my_strcat(str, tmp);
    char buff[100] = {0};
    size_t bufsize = 100;
    readlink(str, buff, bufsize), buff[99] = '\0';
    if (buff[0] == '\0') stat(str, &fileStat);
    else lstat(str, &fileStat);
    ternary_land(fileStat), my_printf(" %d", fileStat.st_nlink);
    my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
    my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
    if ((fileStat.st_rdev) != 0) { my_printf(" %d,", fileStat.st_rdev/256);
    my_printf(" %d", (fileStat.st_rdev % 256));
    } else my_printf(" %d", fileStat.st_size);
    char *date = ctime(&fileStat.st_mtime);
    date[16] = '\0', date += 4, my_printf(" %s", date), my_printf(" %s", tmp);
    if (buff[0] != '\0') my_printf(" -> %s\n", buff);
    else my_printf("\n");
    free(str);
}