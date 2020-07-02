/*
** EPITECH PROJECT, 2020
** handle_client
** File description:
** handle_client
*/

#include "server_ftp.h"

static int read_prompt(client_t *client_data)
{
    char *line;
    char **tab;
    int i;

    line = get_next_line(client_data->fd);
    if (line && strcmp(line, "") != 0 && strcmp(line, "\n") != 0) {
        for (i = 0; line[i] != '\0' && line[i] != '\n'; ++i);
        line[i] = '\0';
        tab = str_to_tab(line, "\t\n\v\f\r ");
        if (!tab)
            dprintf(client_data->fd, "%d\n", UNKNOW);
        else if (use_command(client_data, tab) != 0)
            dprintf(client_data->fd, "%d\n", UNKNOW);
    }
    if (!line || client_data->log_out)
        return 1;
    return 0;
}

void handle_client(client_t *client_data)
{
    if (client_data && read_prompt(client_data))
        return;
}