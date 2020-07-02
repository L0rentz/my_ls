/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** my.h
*/

#ifndef MY_H
#define MY_H

#include "my_printf/my_printf.h"

#include <sys/types.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef enum
{
    false,
    true
} bool;

typedef struct dlist_node_s
{
    char *name;
    time_t mdate;
    struct dlist_node_s *back;
    struct dlist_node_s *next;
} dlist_node_t, node_t;

typedef struct dlist_s
{
    unsigned int length;
    struct dlist_node_s *begin;
    struct dlist_node_s *end;
} dlist_t;

dlist_t *new_list(void);
bool is_empty_list(dlist_t *li);
dlist_node_t *new_dlist_node(char *str);
void print_list(dlist_t *li);
dlist_t *push_back_list(dlist_t *li, char *str);
dlist_t *push_front_list(dlist_t *li, char *str);
dlist_t *pop_front_list(dlist_t *li);
dlist_t *pop_back_list(dlist_t *li);
dlist_t *clear_list(dlist_t *li);

typedef struct flags_s
{
    int lpd;
    int R;
    int d;
    int r;
    int t;
} flags_t;

void no_arg(void);
void no_arg_rev(void);
void no_arg_l(int argc);
void no_flag(char **argv, struct dirent *Dirent);
void no_flag_rev(char **argv, int argc);
int str_bubble_sort(dlist_t *mylist);
dlist_t *sort_alpha_order(dlist_t *mylist);
void print_list_lflag(dlist_t *li);
void print_list_rev(dlist_t *li);
void print_ld_rev(dlist_t *li);
void print_ld(dlist_t *li);
void print_ld_no_arg(void);
void ternary_land(struct stat fileStat);
void d_flag_switch(flags_t *check, char **argv);
void no_flag_no_arg_rev(flags_t *check, int argc, char **argv);
void l_flag_no_arg(flags_t *check);
dlist_t *d_flag(flags_t *check, char **argv);
void print_rights_dot(dlist_node_t *tmp, struct stat fileStat, dlist_t *li);
void print_rights(char *tmp, char *argv, struct stat fileStat);
int blocks_calcul(dlist_t *mylist);
int blocks_calcul_multi(dlist_t *mylist, char *argv);
void l_flag(flags_t *check, char **argv, int argc);
void print_lflag(dlist_t *li, char *argv);
void print_lflag_rev(dlist_t *li, char *argv);
void print_l_file(char *argv);
void no_rev_l_2(char *argv, int check_file, DIR *Dir, int nb);
void rev_l_2(char *argv, int check_file, DIR *Dir, int nb);
void t_flag_no_arg(flags_t *check);
void no_rev_l_time(char *argv, int *count, int nb);
dlist_t *sort_modif_time(dlist_t *mylist);
dlist_t *set_time(dlist_t *mylist);
dlist_t *set_time_ar(dlist_t *mylist, char *argv);
void rev_l_time(char *argv, int *count, int nb);
void only_flag_t(void);
void t_flag_args(char **argv);
void t_flag_args_rev(char **argv, int argc);

int my_getopt(char * const argv[], const char *optstring, char *opt_err);
int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);

#endif
