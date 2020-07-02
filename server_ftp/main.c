/*
** EPITECH PROJECT, 2020
** main
** File description:
** ftp
*/

#include "server_ftp.h"

static void helper(void)
{
    printf("Usage: ./server [port] [path]\n");
}

static void sig_handler(int signum UNUSED)
{
    printf("\n");
    exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    server_t *server_data = malloc(sizeof(server_t));

    if (!server_data)
        return EXIT_ERROR;
    if (ac < 3) {
        helper();
        return EXIT_ERROR;
    }
    if (ac == 2 && (strcmp(av[0], "--help") == 0 || strcmp(av[1], "-h") == 0)) {
        helper();
        return EXIT_SUCCESS;
    }
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    server_initialization(server_data, atoi(av[1]), av[2]);
    server_loop(server_data);
    return EXIT_SUCCESS;
}