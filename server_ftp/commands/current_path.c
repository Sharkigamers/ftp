/*
** EPITECH PROJECT, 2020
** current_path
** File description:
** current_path
*/

#include "server_ftp.h"

void print_working_path(client_t *client_data, char **tab UNUSED)
{
    char *current_path;

    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else {
        current_path = malloc(sizeof(char) * MAX_PATH);
        getcwd(current_path, MAX_PATH);
        dprintf(client_data->fd, "%d \"%s\"\n", PATH_NAME, current_path);
        free(current_path);
    }
}
