/*
** EPITECH PROJECT, 2020
** connexion
** File description:
** connexion
*/

#include "server_ftp.h"

static int accept_connection(server_t *server_data)
{
    int socket = 0;

    socket = accept(server_data->server_fd, (struct sockaddr *)
    &server_data->address, (socklen_t *)&server_data->address_size);
    if (!socket) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("/!\\ * Connection from %s:%d\n",
    inet_ntoa(server_data->address.sin_addr), server_data->port);
    return socket;
}

static int max_fd(client_t **client, int fd_server)
{
    int max = 0;

    for (int i = 0; i < MAX_CLIENT; i++)
        if (client[i] != NULL)
            max = (client[i]->fd > max ? client[i]->fd : max);
    return (fd_server > max ? fd_server : max);
}

static void is_new_client(server_t *server_data, client_t **client)
{
    for (int i = 0; i < MAX_CLIENT; ++i) {
        if (!client[i]) {
            client[i] = client_initialisation(server_data, "127.0.0.1");
            dprintf(client[i]->fd, "%d\n", CONNECTION_ESTABLISH);
            break;
        }
    }
}

static void new_and_current_connect(server_t *server_data, client_t **client,
fd_set read_fd_set)
{
    if (FD_ISSET(server_data->server_fd, &read_fd_set)) {
        server_data->client_fd = accept_connection(server_data);
        is_new_client(server_data, client);
    }
    for (int i = 0; i < MAX_CLIENT; ++i) {
        if (client[i] && FD_ISSET(client[i]->fd, &read_fd_set))
            handle_client(client[i]);
        if (client[i] && client[i]->log_out == true) {
            close(client[i]->fd);
            client[i] = NULL;
        }
    }
}

void connection(server_t *server_data, client_t **client, fd_set read_fd_set)
{
    FD_ZERO(&read_fd_set);
    FD_SET(server_data->server_fd, &read_fd_set);
    for (int i = 0; i < MAX_CLIENT; ++i) {
        if (client[i] && client[i]->fd > 0)
            FD_SET(client[i]->fd, &read_fd_set);
    }
    if (select(max_fd(client, server_data->server_fd) + 1, &read_fd_set,
    NULL, NULL, NULL) < 0) {
        exit(EXIT_FAILURE);
    }
    new_and_current_connect(server_data, client, read_fd_set);
}
