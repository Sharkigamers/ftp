/*
** EPITECH PROJECT, 2020
** store
** File description:
** store
*/

#include "server_ftp.h"

int get_and_write(client_t *client_data, char **tab, int fd_store)
{
    int file = open(tab[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    char *file_content = NULL;

    if (!file)
        return 1;
    dprintf(client_data->fd, "%d\n", FILE_STATUS_OK);
    while (1) {
        file_content = get_next_line(fd_store);
        if (!file_content)
            break;
        dprintf(file, "%s\n", file_content);
        free(file_content);
    }
    close(file);
    dprintf(client_data->fd, "%d\n", CLOSING_DATA_CONNECTION);
    return 0;
}

int uploading_file(client_t *client_data, char **tab)
{
    struct sockaddr_in address;
    socklen_t address_size = sizeof(address);
    int store_fd;

    if (client_data->fd_mod == BASIC_FD_MOD)
        store_fd = client_data->fd_mod;
    else
        store_fd = accept(client_data->fd_mod, (struct sockaddr *)&address,
        &address_size);
    if (store_fd == -1)
        return 1;
    if (get_and_write(client_data, tab, store_fd))
        dprintf(client_data->fd, "%d\n", FAIL_OPEN_FILE);
    close(client_data->fd_mod);
    client_data->fd_mod = 0;
    return 0;
}

void store(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (client_data->fd_mod == NONE || !tab[1] ||
    uploading_file(client_data, tab))
        dprintf(client_data->fd, "%d\n", WRONG_MOD);
}