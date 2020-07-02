/*
** EPITECH PROJECT, 2020
** delete
** File description:
** delete
*/

#include "server_ftp.h"

void delete_file(client_t *client_data, char **tab)
{
    struct stat status;

    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    if (tab[1] && (stat(tab[1], &status) < 0 || !S_ISREG(status.st_mode) ||
    unlink(tab[1]) == -1))
        dprintf(client_data->fd, "%d\n", UNKNOWN_DIRECTORY);
    else
        dprintf(client_data->fd, "%d\n", REQUEST_FILE_ACTION_OK);
}