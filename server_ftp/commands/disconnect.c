/*
** EPITECH PROJECT, 2020
** disconnect
** File description:
** disconnect
*/

#include "server_ftp.h"

void log_out(client_t *client_data, char **tab UNUSED)
{
    dprintf(client_data->fd, "%d\n", LOG_OUT);
    client_data->log_out = true;
}