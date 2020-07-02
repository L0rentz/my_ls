/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** my_utils
*/

#include "my.h"

int my_strlen(char const *str)
{
    int i = 0;
    if (str == 0)
        return (0);
    for (; str[i]; i++);
    return (i);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    while (1) {
        for (; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
        if (s2[i] <= 'Z' && s2[i] >= 'A') {
            if (s1[i] == s2[i] + 32)
                i++;
            else
                return (s1[i] - (s2[i] + 32));
        }
        else if (s1[i] <= 'Z' && s1[i] >= 'A') {
            if (s2[i] == s1[i] + 32)
                i++;
            else
                return ((s1[i] + 32) - s2[i]);
        }
        else
            return (s1[i] - s2[i]);
    }
}

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int size_dest = my_strlen(dest);
    while (src[i] != '\0') {
        dest[size_dest++] = src[i];
        i++;
    }
    dest[size_dest++] = '\0';
    return (dest);
}
