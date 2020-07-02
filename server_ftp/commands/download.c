/*
** EPITECH PROJECT, 2020
** download
** File description:
** download
*/

#include "server_ftp.h"

int transfer(client_t *client_data, char **tab, int download_fd)
{
    FILE *file = fopen(tab[1], "r+");
    char file_content[4096];

    if (!file)
        return 1;
    dprintf(client_data->fd, "%d\n", FILE_STATUS_OK);
    while (1) {
        if (!fgets(file_content, 4096, file))
            break;
        dprintf(download_fd, "%s", file_content);
    }
    fclose(file);
    close(download_fd);
    close(client_data->fd_mod);
    dprintf(client_data->fd, "%d\n", CLOSING_DATA_CONNECTION);
    return 0;
}

int downloading_file(client_t *client_data, char **tab)
{
    struct sockaddr_in address;
    socklen_t address_size = sizeof(address);
    int download_fd;

    if (client_data->fd_mod == BASIC_FD_MOD)
        download_fd = client_data->fd_mod;
    else
        download_fd = accept(client_data->fd_mod, (struct sockaddr *)&address,
        &address_size);
    if (download_fd == -1)
        return 1;
    if (transfer(client_data, tab, download_fd))
        dprintf(client_data->fd, "%d\n", FAIL_OPEN_FILE);
    client_data->fd_mod = NONE;
    return 0;
}

void download(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    if (client_data->fd_mod == NONE || !tab[1] ||
    downloading_file(client_data, tab))
        dprintf(client_data->fd, "%d\n", WRONG_MOD);
}