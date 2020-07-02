/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#include "server_ftp.h"

void server_loop(server_t *server_data)
{
    client_t **client = malloc(sizeof(client) * (MAX_CLIENT + 1));
    fd_set read_fd_set;

    for (int i = 0; i < MAX_CLIENT; i++)
        client[i] = NULL;
    client[MAX_CLIENT] = NULL;
    for (;;) {
        connection(server_data, client, read_fd_set);
    }
    free(client);
}
