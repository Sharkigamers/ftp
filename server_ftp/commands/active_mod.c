/*
** EPITECH PROJECT, 2020
** active_mode
** File description:
** active_mod
*/

#include "server_ftp.h"

int init_active_socket(client_t *client_data)
{
    struct protoent *protent = NULL;

    if (client_data->fd_mod != UNDEF)
        close(client_data->fd_mod);
    protent = getprotobyname("TCP");
    if (!protent)
        return (1);
    client_data->fd_mod = socket(AF_INET, SOCK_STREAM, protent->p_proto);
    if (client_data->fd_mod == UNDEF)
        return 1;
    return 0;
}

int init_active_mod(client_t *client_data, char **host_port)
{
    char *ip = get_ip_from_tab(host_port, '.');
    struct sockaddr_in address;
    socklen_t address_size = sizeof(address);

    if (init_active_socket(client_data))
        return 1;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(host_port[4]) * 256 + atoi(host_port[5]));
    address.sin_addr.s_addr = inet_addr(ip);
    if (connect(client_data->fd_mod, (struct sockaddr *)&address,
    address_size) == -1)
        return (1);
    client_data->activated_mod = ACTIVE;
    free(ip);
    return 0;
}

int active_active_mod(client_t *client_data, char **tab)
{
    short return_value = 0;
    int i = 0;
    char **host_port;

    host_port = str_to_tab(tab[1], ",");
    if (!host_port)
        return 1;
    for (; host_port[i]; ++i);
    if (i < 6)
        return 1;
    return_value = init_active_mod(client_data, host_port);
    for (int i = 0; host_port[i]; ++i)
        free(host_port[i]);
    free(host_port);
    return return_value;
}

void active_mod(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (!tab[1] || active_active_mod(client_data, tab) == 1)
        dprintf(client_data->fd, "%d\n", ERROR);
    else {
        dprintf(client_data->fd, "%d\n", ACTIVE_MOD);
    }
}
