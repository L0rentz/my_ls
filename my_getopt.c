/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** my_getopt
*/

#include "my.h"

int opt_number(char * const argv[])
{
    int len = 0;
    for (int count = 0, i = 0; argv[i] != NULL; i++) {
        count = my_strlen(argv[i]);
        if (count > 1 && argv[i][0] == '-')
            len += count - 1;
    }
    return (len);
}

char *fill_opt_buff(char * const argv[], char *opt)
{
    int index = 0;
    for (int i = 0; argv[i] != NULL; i++) {
        for (int j = 1; argv[i][0] == '-' && argv[i][j] != '\0'
        && my_strlen(argv[i]) > 1; j++, index++)
            opt[index] = argv[i][j];
    }
    opt[index] = '\0';
    return (opt);
}

int my_getopt(char * const argv[], const char *optstring, char *opt_err)
{
    static int fill = 0, len = 0, i = 0;
    static char *opt = NULL;
    if (fill != 1) {
        len = opt_number(argv);
        opt = malloc(sizeof(char) * len + 1);
        opt = fill_opt_buff(argv, opt);
        fill = 1;
    } else if (i == len) {
        free(opt);
        return (-1);
    }
    for (int j = 0; optstring[j] != '\0' && opt[i] != '\0'; j++) {
        if (optstring[j] == opt[i]) {
            i++;
            return (optstring[j]);
        }
    }
    *opt_err = opt[i];
    free(opt);
    return (-1);
}