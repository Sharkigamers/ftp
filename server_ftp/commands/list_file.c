/*
** EPITECH PROJECT, 2020
** list_file
** File description:
** list_file
*/

#include "server_ftp.h"

static void list_working_directory(char **tab, int list_fd)
{
    FILE *pp;
    char str[4096];
    char *flags = strdup("ls -l ");

    if (tab[1]) {
        flags = realloc(flags, sizeof(char) *
        (strlen(flags) + strlen(tab[1]) + 2));
        flags = strcat(flags, tab[1]);
    }
    pp = popen(flags, "r");
    if (!pp)
        return;
    while (fgets(str, 4096, pp))
        dprintf(list_fd, "%s", str);
    fclose(pp);
    free(flags);
}

static void accept_list(client_t *client_data, char **tab)
{
    struct sockaddr_in address;
    socklen_t address_size = sizeof(address);
    int list_fd;

    if (client_data->fd_mod == BASIC_FD_MOD)
        list_fd = client_data->fd_mod;
    else
        list_fd = accept(client_data->fd_mod, (struct sockaddr *)&address,
        &address_size);
    if (list_fd == -1)
        return;
    list_working_directory(tab, list_fd);
    close(list_fd);
    client_data->fd_mod = 0;
}

void print_list_file(client_t *client_data, char **tab)
{
    if (!client_data->is_login)
        dprintf(client_data->fd, "%d\n", ERROR_LOOGGIN);
    else if (client_data->activated_mod != PASSIVE)
        dprintf(client_data->fd, "%d\n", DATA_CONNECTION);
    else {
        dprintf(client_data->fd, "%d\n", FILE_STATUS_OK);
        accept_list(client_data, tab);
        dprintf(client_data->fd, "%d\n", CLOSING_DATA_CONNECTION);
    }
}