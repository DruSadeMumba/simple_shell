#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#define GET_LINE 0
extern char **environ;

/**
 * struct lists - list
 * @num: number
 * @str: string
 * @next: next node
 */
typedef struct lists
{
	int num;
	char *str;
	struct lists *next;
} list_t;

/**
 * struct shdata - data
 * @arg: arg
 * @argv: vector
 * @path: path
 * @argc: count
 * @count: count
 * @errnum: errnum
 * @lineflags: flags
 * @fname: file
 * @env: env
 * @hist: hist
 * @alias: alias
 * @environ: env
 * @cenv: env
 * @status: status
 * @cmdbuf: cmd
 * @cbt: cbt
 * @readfd: fd
 * @histcount: count
 */
typedef struct shdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count;
	int errnum;
	int lineflags;
	char *fname;
	list_t *env;
	list_t *hist;
	list_t alias;
	char **environ;
	int cenv;
	int status;
	char **cmdbuf;
	int cbt;
	int readfd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtincommands - builtin
 * @type: type
 * @func: function
 */
typedef struct builtincommands
{
	char *type;
	int (*func)(data_t *);
} bic_t;

int handlers(data_t *, char **);
int _findbic(data_t *);
void _findcmd(data_t *);
void _forkcmd(data_t *);
int _cmd(data_t *, char *);
char *_dup(char *, int, int);
char *_path(data_t *, char *, char *);
void _eputs(char *);
void _puts(char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);
int _putchar(char);
char *_firstchar(const char *, const char *);
char **strtow(char *, char *);
void _free(char **);
int __free(void **);
void _freelist(list_t **);
void *_realloc(void *, unsigned int, unsigned int);
int _isdelimiter(char, char *);
int mode(data_t *);
void _printerr(data_t *, char *);
int _printd(int, int);
char *_convertint(long int, int, int);
void _comments(char *);
int _exithandler(data_t *);
int _cd(data_t *);
int _help(data_t *);
ssize_t _getinput(data_t *);
int _getline(data_t *, char **, size_t *);
void _handler(int);
void _cleardata(data_t *);
void _setdata(data_t *, char **);
void _freedata(data_t *, int);
int _env(data_t *);
int _envlist(data_t *);
char *_getenv(data_t *, const char *);
int _setsenv(data_t *);
int _unsetsenv(data_t *);
char **_getenviron(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);
int _history(data_t *);
char *_gethistory(data_t *);
int _writehistory(data_t *);
int _readhistory(data_t *);
int _historylist(data_t *, char *, int);
int _historynums(data_t *);
list_t *_addendnode(list_t **, const char *, int);
int _deletenode(list_t **, unsigned int);
list_t *_nodestart(list_t *, char *, char);
ssize_t _getnode(list_t *, list_t *);
size_t _llen(const list_t *);
char **_ltostr(list_t *);
size_t _printlist(const list_t *);
size_t _printslists(const list_t *);
int _ischain(data_t *, char *, size_t *);
void _checkchain(data_t *, char *, size_t *, size_t, size_t);
int _changechains(data_t *);
int _changestrings(char **, char *);
int _alias(data_t *);
int _changealias(data_t *);

#endif
