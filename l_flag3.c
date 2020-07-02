/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** l_flag3
*/

#include "my.h"

void print_l_file(char *argv)
{
    struct stat fileStat;
    stat(argv, &fileStat);
    ternary_land(fileStat);
    my_printf(" %d", fileStat.st_nlink);
    my_printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
    my_printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
    if ((fileStat.st_rdev) != 0) { my_printf(" %d,", fileStat.st_rdev/256);
    my_printf(" %d", (fileStat.st_rdev % 256));
    } else my_printf(" %d", fileStat.st_size);
    char *date = ctime(&fileStat.st_mtime);
    date[16] = '\0';
    date += 4;
    my_printf(" %s", date);
    my_printf(" %s\n", argv);
}

void no_rev_l_2_time(char *argv, int check_file, DIR *Dir, int nb)
{
    if (Dir != NULL) {
        dlist_t *mylist = new_list();
        struct dirent *Dirent;
        while ((Dirent = readdir(Dir)) != NULL) {
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        } mylist = set_time_ar(mylist, argv);
        mylist = sort_modif_time(mylist);
        if (check_file == 1)
            my_printf("\n");
        if (nb != 1)
            my_printf("%s:\n", argv);
        if (mylist != NULL)
            my_printf("total %d\n", blocks_calcul_multi(mylist, argv));
        print_lflag(mylist, argv);
        mylist = clear_list(mylist), closedir(Dir);
    }
}

void no_rev_l_time(char *argv, int *count, int nb)
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
        no_rev_l_2_time(argv, check_file, Dir, nb);
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

void rev_l_2_time(char *argv, int check_file, DIR *Dir, int nb)
{
    if (Dir != NULL) {
        dlist_t *mylist = new_list();
        struct dirent *Dirent;
        while ((Dirent = readdir(Dir)) != NULL) {
            if (Dirent->d_name[0] != '.')
                mylist = push_back_list(mylist, Dirent->d_name);
        } mylist = set_time_ar(mylist, argv);
        mylist = sort_modif_time(mylist);
        if (check_file == 1)
            my_printf("\n");
        if (nb != 1)
            my_printf("%s:\n", argv);
        if (mylist != NULL)
            my_printf("total %d\n", blocks_calcul_multi(mylist, argv));
        print_lflag_rev(mylist, argv);
        mylist = clear_list(mylist), closedir(Dir);
    }
}

void rev_l_time(char *argv, int *count, int nb)
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
        rev_l_2_time(argv, check_file, Dir, nb);
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