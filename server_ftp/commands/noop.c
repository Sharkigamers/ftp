/*
** EPITECH PROJECT, 2020
** noop
** File description:
** noop
*/

#include "server_ftp.h"

void noop(client_t *client_data, char **tab UNUSED)
{
    if (!client_data->is_login) {
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    } else {
        dprintf(client_data->fd, "%d\n", DO_NOTHING);
    }
}