/*
** EPITECH PROJECT, 2020
** help
** File description:
** help
*/

#include "server_ftp.h"

void help(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else {
        dprintf(client_data->fd, "214 ");
        if (!tab[1])
            dprintf(client_data->fd,
            "Commands (1): USER PASS CWD CDUP QUIT DELE PWD\n");
        else
            dprintf(client_data->fd,
            "Commands (2): PASV PORT HELP NOOP RETR STOR LIST\n");
    }
}