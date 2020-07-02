/*
** EPITECH PROJECT, 2020
** initialization
** File description:
** initialization
*/

#include "server_ftp.h"

client_t *client_initialisation(server_t *server_data, char *ip)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (!new_client)
        return NULL;
    new_client->quit = false;
    new_client->log_out = false;
    new_client->is_login = false;
    new_client->fd = server_data->client_fd;
    new_client->fd_mod = UNDEF;
    new_client->activated_mod = NOTHING;
    new_client->port_mod = 0;
    new_client->ip = ip;
    new_client->username = NULL;
    new_client->password = NULL;
    new_client->dir_path = strdup(server_data->dir_path);
    return new_client;
}

void fill_structure(server_t *server_data, int port, char *dir_path)
{
    if (port < 0) {
        fprintf(stderr, "Error: Invalid port");
        exit(EXIT_ERROR);
    }
    if (chdir(dir_path) == -1) {
        fprintf(stderr, "Error: Bad path\n");
        exit(EXIT_ERROR);
    }
    server_data->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_data->server_fd == -1) {
        fprintf(stderr, "Error: Invalid file descriptor");
        exit(EXIT_ERROR);
    }
    server_data->port = port;
    server_data->dir_path = dir_path;
    server_data->address_size = sizeof(server_data->address);
    server_data->address.sin_family = AF_INET;
    server_data->address.sin_port = htons(server_data->port);
    server_data->address.sin_addr.s_addr = INADDR_ANY;
}

void init_basics_server(server_t *server_data)
{
    int opt = 1;

    if (setsockopt(server_data->server_fd, SOL_SOCKET, SO_REUSEADDR,
    (char *)&opt, sizeof(opt)) < 0 ) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    if (bind(server_data->server_fd, (struct sockaddr *)&server_data->address,
    sizeof(server_data->address)) < 0) {
        perror("bind failed");
        exit(EXIT_ERROR);
    }
    if (listen(server_data->server_fd, 30) < 0) {
        perror("listen failed");
        exit(EXIT_ERROR);
    }
}

void server_initialization(server_t *server_data, int port,
char *dir_path)
{
    fill_structure(server_data, port, dir_path);
    if (server_data->server_fd == -1) {
        perror("socket failed");
        exit(EXIT_ERROR);
    }
    init_basics_server(server_data);
    printf("Listening to port %hu...\n", server_data->port);
}
