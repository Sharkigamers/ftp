/*
** EPITECH PROJECT, 2020
** passive_mod
** File description:
** passive_mod
*/

#include <time.h>

#include "server_ftp.h"

void display_passive_mod(client_t *client_data, struct sockaddr_in address)
{
    char *modificator_ip = strdup(inet_ntoa(address.sin_addr));
    char **ip = str_to_tab(modificator_ip, ".");
    char *display_ip = tab_to_str(ip, ',');

    dprintf(client_data->fd, "%d\n", PASSIVE_MOD);
    free(modificator_ip);
    free(display_ip);
    for (int i = 0; ip[i]; ++i)
        free(ip[i]);
    free(ip);
}

static int init_passive_socket(client_t *client_data,
struct sockaddr_in *address)
{
    struct protoent *protent = NULL;
    int random_port;

    srand(time(NULL));
    random_port = rand() % 10000 + 1024;
    printf("Pasv connect : %d\n", random_port);
    if (client_data->fd_mod != UNDEF)
        close(client_data->fd_mod);
    protent = getprotobyname("TCP");
    if (!protent)
        return (1);
    client_data->fd_mod = socket(AF_INET, SOCK_STREAM, protent->p_proto);
    if (client_data->fd_mod == UNDEF)
        return 1;
    address->sin_family = AF_INET;
    address->sin_port = htons(random_port);
    address->sin_addr.s_addr = inet_addr(client_data->ip);
    return 0;
}

int active_passive_mod(client_t *client_data, struct sockaddr_in *address)
{
    if (init_passive_socket(client_data, address))
        return 1;
    if (bind(client_data->fd_mod, (struct sockaddr *)address,
    sizeof(*address)) < 0)
        return 1;
    if (listen(client_data->fd_mod, 30) < 0)
        return 1;
    client_data->port_mod = ntohs(address->sin_port);
    return 0;
}

void passive_mod(client_t *client_data, char **tab UNUSED)
{
    struct sockaddr_in address;

    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (active_passive_mod(client_data, &address) == 1)
        dprintf(client_data->fd, "%d\n", ERROR);
    else {
        client_data->activated_mod = PASSIVE;
        display_passive_mod(client_data, address);
    }
}