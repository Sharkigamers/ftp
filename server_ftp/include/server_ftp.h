/*
** EPITECH PROJECT, 2020
** server_ftp
** File description:
** server_ftp
*/

#ifndef SERVER_FTP_H_
#define SERVER_FTP_H_

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#include <limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <netdb.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#define UNUSED __attribute__((unused))
#define EXIT_ERROR 84
#define MAX 1024
#define MAX_PATH 250
#define MAX_CLIENT 30
#define READ_SIZE 1024

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#define CONNECTION_ESTABLISH 220
#define USER_LOGING_MISSING_PASSWORD 331
#define MISSING_USERNAME 332
#define ALREADY_LOGGED 230
#define USER_LOGING 230
#define ERROR_LOOGGIN 530
#define DO_NOTHING 200
#define UNKNOW 500
#define LOG_OUT 221
#define DATA_CONNECTION 425
#define FILE_STATUS_OK 150
#define CLOSING_DATA_CONNECTION 226
#define PATH_NAME 257
#define ERROR 500
#define MOVE_PARENT 200
#define MOVE_DIR 250
#define REQUEST_FILE_ACTION_OK 250
#define PASSIVE_MOD 227
#define ACTIVE_MOD 200
#define WRONG_MOD 425
#define FAIL_OPEN_FILE 530
#define UNKNOWN_DIRECTORY 550

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

typedef enum activated_mod {
    NOTHING,
    PASSIVE,
    ACTIVE
} a_mod_t;

typedef enum file_descriptor_mod {
    UNDEF = -1,
    NONE = 0,
    BASIC_FD_MOD = 2
} mod_fd_t;

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

typedef struct server_ressources
{
    unsigned short port;
    int server_fd;
    int client_fd;
    char *dir_path;
    struct sockaddr_in address;
    socklen_t address_size;
} server_t;

typedef struct client_ressources
{
    bool quit;
    bool is_login;
    bool log_out;
    int fd;
    mod_fd_t fd_mod;
    a_mod_t activated_mod;
    int port_mod;
    char *ip;
    char *username;
    char *password;
    char *dir_path;
} client_t;

typedef struct command_ressources
{
    char *name;
    void (*function)(client_t *client_data, char **tab);
} command_t;

typedef struct linked_client
{
    client_t *client;
    struct linked_client *next;
} l_client_t;

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

void server_initialization(server_t *serever_data, int port, char *host_ip);
void server_loop(server_t *server_data);
void connection(server_t *server_data, client_t **client, fd_set read_fd_set);
void handle_client(client_t *client_data);
client_t *client_initialisation(server_t *server_data, char *ip);

int use_command(client_t *client_data, char **tab);
void user(client_t *client_data, char **tab);
void password(client_t *client_data, char **tab);
void noop(client_t *client_data, char **tab);
void log_out(client_t *client_data, char **tab);
void help(client_t *client_data, char **tab);
void print_list_file(client_t *client_data, char **tab);
void print_working_path(client_t *client_data, char **tab);
void change_directory(client_t *client_data, char **tab);
void change_parent_directory(client_t *client_data, char **tab);
void delete_file(client_t *client_data, char **tab);
void passive_mod(client_t *client_data, char **tab);
void active_mod(client_t *client_data, char **tab);
void store(client_t *client_data, char **tab);
void download(client_t *client_data, char **tab);

char **str_to_tab(char *line, char *delimitors);
char *tab_to_str(char **tab, char delimitor);
char *get_ip_from_tab(char **tab, char delimitor);
void append_string(char *dest, char *src, char add);
char *get_next_line(int fd);

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#endif /* !SERVER_FTP_H_ */
