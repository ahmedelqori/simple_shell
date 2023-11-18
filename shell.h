#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOKEN_BUFSIZE 128
#define TOKEN_DELIM " \t\r\n\a"

/* Global environment */
extern char **environ;


/**
 * struct data - Runtime data struct. 
 * @argv: argument vector
 * @input: user-provided command line input. 
 * @args: tokens parsed from the command line input. 
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **argv;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - singly linked list
 * @separator: ; | &
 * @next: next node
 * Description: singly linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - singly linked list
 * @line: command line
 * @next: next node
 * Description: singly linked list to store command lines input
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct rd_var_list - singly linked list
 * @len_var: length of the variable
 * @value: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: singly linked list to store variables
 */
typedef struct rd_var_list
{
	int len_var;
	char *value;
	int len_val;
	struct rd_var_list *next;
} rd_var;

/**
 * struct builtin_s - Builtin struct for command and arguments. 
 * @name: command names (eg cd, exit, env) 
 * @f:  pointer to function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *dataSh);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
rd_var *add_rdvar_node(rd_var **head, int lenvar, char *var, int lenval);
void free_rdvar_list(rd_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdpr(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int comp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void ver_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_ops(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *dataSh, char *input, int i, int boolean);
int check_syntax_error(data_shell *dataSh, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *dataSh);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int boolean);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *dataSh);
int split_commands(data_shell *dataSh, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(rd_var **he, char *in, data_shell *data);
int check_vars(rd_var **he, char *in, char *st, data_shell *data);
char *replaced_input(rd_var **head, char *input, char *new_input, int nlen);
char *rev_var(char *input, data_shell *dataSh);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(data_shell *dataSh);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmmd, char **_environ);
int is_executable(data_shell *dataSh);
int check_error_cmd(char *dir, data_shell *dataSh);
int cmd_exec(data_shell *dataSh);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *dataSh);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *dataSh);
int _setenv(data_shell *dataSh);
int _unsetenv(data_shell *dataSh);

/* cd.c */
void cd_dot(data_shell *dataSh);
void cd_to(data_shell *dataSh);
void cd_previous(data_shell *dataSh);
void cd_to_home(data_shell *dataSh);

/* cd_shell.c */
int cd_shell(data_shell *dataSh);

/* get_builtin */
int (*get_builtin(char *cmmd))(data_shell *dataSh);

/* _exit.c */
int exit_shell(data_shell *dataSh);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *dataSh);
char *error_not_found(data_shell *dataSh);
char *error_exit_shell(data_shell *dataSh);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *dataSh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *dataSh);


/* get_error.c */
int get_error(data_shell *dataSh, int errval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(data_shell *dataSh);

#endif
