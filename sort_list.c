/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** sort_list
*/

#include "my.h"

int str_bubble_sort(dlist_t *mylist)
{
    dlist_node_t *tmp = mylist->begin;
    int count = 0;
    while (tmp->next != NULL) {
        if (my_strcmp(tmp->name, tmp->next->name) > 0) {
            count++;
            char *str = tmp->name;
            tmp->name = tmp->next->name;
            tmp->next->name = str;
        }
        tmp = tmp->next;
    }
    if (count != 0)
        return (1);
    else
        return (0);
}

dlist_t *sort_alpha_order(dlist_t *mylist)
{
    if (mylist != NULL)
        while (errno != ENOTDIR && str_bubble_sort(mylist) != 0);
    return (mylist);
}