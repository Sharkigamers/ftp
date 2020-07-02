/*
** EPITECH PROJECT, 2020
** login
** File description:
** login
*/

#include "server_ftp.h"

void user(client_t *client_data, char **tab)
{
    if (client_data->is_login)
        dprintf(client_data->fd, "%d\n", ALREADY_LOGGED);
    else if (tab[1]) {
        if (client_data->username)
            free(client_data->username);
        client_data->username = strdup(tab[1]);
        dprintf(client_data->fd, "%d\n", USER_LOGING_MISSING_PASSWORD);
    } else
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
}

void password(client_t *client_data, char **tab)
{
    if (client_data->is_login)
        dprintf(client_data->fd, "%d\n", ALREADY_LOGGED);
    else {
        if (client_data->username && !tab[1] &&
        strcmp(client_data->username, "Anonymous") == 0) {
            if (client_data->password)
                free(client_data->password);
            if (tab && tab[1])
                client_data->password = strdup(tab[1]);
            else
                client_data->password = "";
            client_data->is_login = true;
            dprintf(client_data->fd, "%d\n", USER_LOGING);
        } else if (client_data->username)
            dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
        else
            dprintf(client_data->fd, "%d\n", MISSING_USERNAME);
    }
}