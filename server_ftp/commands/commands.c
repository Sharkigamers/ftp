/*
** EPITECH PROJECT, 2020
** commands
** File description:
** commands
*/

#include "server_ftp.h"

int use_command(client_t *client_data, char **tab)
{
    static command_t commands[] = {{"USER", &user}, {"PASS", &password},
        {"NOOP", &noop}, {"QUIT", &log_out}, {"HELP", &help},
        {"LIST", &print_list_file}, {"PWD", &print_working_path},
        {"CWD", &change_directory}, {"CDUP", &change_parent_directory},
        {"DELE", &delete_file}, {"PASV", &passive_mod}, {"PORT", &active_mod},
        {"STOR", &store}, {"RETR", &download}, {NULL, NULL}};

    for (int i = 0; commands[i].name != NULL; ++i) {
        if (strcmp(commands[i].name, tab[0]) == 0) {
            (*commands[i].function)(client_data, tab);
            return 0;
        }
    }
    return 1;
}