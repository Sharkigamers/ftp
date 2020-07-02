/*
** EPITECH PROJECT, 2020
** move_directory
** File description:
** move_directory
*/

#include "server_ftp.h"

void change_directory(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (!tab[1] || tab[2] || chdir(tab[1]) == -1)
        dprintf(client_data->fd, "%d\n", UNKNOWN_DIRECTORY);
    else
        dprintf(client_data->fd, "%d\n", MOVE_DIR);
}

void change_parent_directory(client_t *client_data, char **tab UNUSED)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (chdir("../") == -1)
        dprintf(client_data->fd, "%d\n", UNKNOWN_DIRECTORY);
    else
        dprintf(client_data->fd, "%d\n", MOVE_PARENT);
}
