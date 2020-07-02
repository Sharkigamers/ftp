/*
** EPITECH PROJECT, 2020
** utils
** File description:
** utils
*/

#include "server_ftp.h"

char **str_to_tab(char *line, char *delimitors)
{
    char **final_tab = malloc(sizeof(char *));
    char *token = strtok(line, delimitors);

    if (!line || !delimitors || !token || !final_tab)
        return NULL;
    for (int i = 0;;) {
        final_tab[i] = strdup(token);
        ++i;
        final_tab = realloc(final_tab, sizeof(char *) * (i + 1));
        token = strtok(NULL, delimitors);
        if (token == NULL) {
            final_tab[i] = NULL;
            break;
        }
    }
    free(token);
    return final_tab;
}

char *tab_to_str(char **tab, char delimitor)
{
    char *line;
    int j = 0;
    int k = 0;

    for (int i = 0; tab[i]; ++i)
        j += strlen(tab[i]) + 1;
    line = malloc(sizeof(char) * j);
    if (!line)
        return NULL;
    for (int i = 0; tab[i]; ++i, ++k) {
        for (int j = 0; tab[i][j]; ++j, ++k)
            line[k] = tab[i][j];
        if (!tab[i + 1])
            break;
        line[k] = delimitor;
    }
    line[k] = '\0';
    return line;
}

char *get_ip_from_tab(char **tab, char delimitor)
{
    unsigned short length_total_strings = 0;
    int j = 0;
    char *ip = malloc(sizeof(char));

    if (!ip)
        return NULL;
    for (int i = 0; i < 4; ++i, ++j) {
        length_total_strings += strlen(tab[i]) + 1;
        ip = realloc(ip, sizeof(char) * (length_total_strings));
        if (!ip)
            return NULL;
        for (int k = 0; tab[i][k]; ++j, ++k)
            ip[j] = tab[i][k];
        ip[j] = delimitor;
    }
    ip[j - 1] = '\0';
    return ip;
}

void append_string(char *dest, char *src, char add)
{
    int i = 0;

    for (; dest[i] != '\0'; ++i);
    for (int j = 0; src[j]; ++j, ++i)
        dest[i] = src[j];
    dest[i] = add;
    dest[i + 1] = '\0';
}
