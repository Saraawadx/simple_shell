#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_str - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 * struct information - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct information
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct built_in - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);
int my_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int alias_print(list_t *node);
int my_alias(info_t *info);
int my_env(info_t *info);
char *get_env(info_t *info, const char *name);
int my_setenv(info_t *info);
int my_unsetenv(info_t *info);
int add_env_list(info_t *info);
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int err_atoi(char *s);
void print_error(info_t *info, char *estr);
int print_dec(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
ssize_t input_buff(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);
char **get_environ(info_t *info);
int unset_env(info_t *info, char *var);
int set_env(info_t *info, char *var, char *value);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
char *get_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *addNode(list_t **head, const char *str, int num);
list_t *addNodeEnd(list_t **head, const char *str, int num);
size_t printList_str(const list_t *j);
int deleteNode_byIndex(list_t **head, unsigned int index);
void freeList(list_t **head_ptr);
size_t listLen(const list_t *j);
char **listTo_strings(list_t *head);
size_t printList(const list_t *j);
list_t *nodeStarts_pre(list_t *node, char *prefix, char c);
ssize_t nodeIndex(list_t *head, list_t *node);
int shh(info_t *info, char **av);
int findBuiltin(info_t *info);
void cmdFind(info_t *info);
void cmdFork(info_t *info);
int freePtr(void **ptr);
int isExec_cmd(info_t *info, char *path);
char *dupChars(char *pathstr, int start, int stop);
char *findPath(info_t *info, char *pathstr, char *cmd);
char *memFill(char *a, char v, unsigned int b);
void freeString(char **qq);
void *reAllocate(void *ptr, unsigned int old_size, unsigned int new_size);
int stringLen(char *a);
int stringComp(char *str1, char *str2);
char *needleStarts(const char *hay_stack, const char *needle);
char *concatStrings(char *dest, char *src);
char *copyString(char *dest, char *src);
char *dupString(const char *str);
void inputString(char *str);
int inputChar(char c);
char **strSplit(char *str, char *s);
char **strSplit_toWords(char *str, char s);
int isCharChain(info_t *info, char *buff, size_t *q);
void ifCheckChain(info_t *info, char *buff, size_t *q, size_t u, size_t len);
int replaceAlias(info_t *info);
int replaceVars(info_t *info);
int replaceString(char **old, char *new);

#endif
