/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:37 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 14:05:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>

/*
**	the prompt to be displayed when input is expected.
*/
# define SHELL_PROMPT "\033[38;5;75m-ish » \033[0;00m"

/*
**	the key for the status code in the environment.
*/
# define STATUS_CODE_KEY "STATUS_CODE"

/*
**	the total amount of errors. Error codes start at 0.
**	this is used to determine the length of the array holding the errors,
**	and to check if an error code is valid.
*/
# define ERR_COUNT 10

/*
**	list of defines for errid.
**	The total amount of errors is defined by ERR_COUNT.
*/
# define ERR_NOERR 0
# define ERR_MALLOCFAIL 1
# define ERR_ACCESS 2
# define ERR_ENVNOWRITE 3
# define ERR_ENVNOTFOUND 4
# define ERR_EMPTYENV 5
# define ERR_INVALID_EXP 6
# define ERR_EXECVE_FAILED 7
# define ERR_FORK_FAILED 8
# define ERR_CMD_NOT_FOUND 9

/*
**	typedef for our error tracking variable errid.
**	like the system errno, it contains a numerical error code.
**	Possible error codes are defined with the prefix 'ERR_'.
*/
typedef unsigned char	t_errid;

/*
**	Struct to store info about the command to execute. Fields:
**	input:		the complete input as given by get_next_line.
**	argc:		amount of arguments for command.
**	argv:		list of arguments for command, extracted from input.
**	path:	absolute path of executable from PATH. empty if builtin.
**	envp:		the environmennt for the command.
*/
typedef struct			s_command
{
	char			*input;
	int				argc;
	char			**argv;
	char			*path;
	char			**envp;
}						t_command;

/*
**	Struct to store the environment variables in a linked list. Fields:
**	key:	The variable name. i.e. HOME
**	value:	The value of the variable. i.e. /Users/lgutter
**	next:	A pointer to the next element in the list of env variables
*/
typedef struct			s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}						t_env;

/*
**	converts the system char **environ to a linked list of our type t_env
**	returns the start of the list on succes, or NULL on failure.
**	(on failure, error will be printed)
*/
t_env					*ft_dup_sys_env(t_errid *errid);

/*
**	takes the env and a key as argument and returns the value.
**	example: 'ft_getenv("PWD");' will return the path of our current directory.
**	when an error occurs, returns NULL.
**	(on failure, error will be printed)
*/
char					*ft_getenv(t_env *env, const char *key);

/*
**	Takes env, a key, value, and either 'y' or 'n' as arguments.
**	If 'key' exists in env and 'overwrite' is 'y', overwrites the value.
**	If 'key' does not exist, adds it to env and sets the value.
**	Returns the following:
**	0 on succes, an errid error code on failure.
**	(on failure, error will be printed)
*/
int						ft_setenv(t_env *env, const char *key,
									const char *value, char overwrite);

/*
**	Takes env, and returs the current status code as an int.
**	if an error occurs, it returns NULL, and an error is printed.
*/
int						ft_getstatus(t_env *env);

/*
**	Takes env and a status code and sets the status code as a str in env.
**	returns 0 on succes, an errid error code on failure.
**	(on failure, error will be printed)
*/
int						ft_setstatus(t_env *env, int status);

/*
**	takes env and a key as argument and removes it from our environment.
**	returns the following:
**	0 on succes, an errid error code on failure.
**	(on failure, error will be printed)
*/
int						ft_unsetenv(t_env *env, const char *key);

/*
**	converts our linked list of type t_env to the the system style char **envp.
**	returns the an char ** on succes, or NULL on failure.
**	(on failure, error will be printed)
*/
char					**ft_convert_env_to_envp(t_env *list_start);

/*
**	prints an error message relevant for the value of errid.
**	returns the given value of errid.
*/
int						ft_print_error(t_errid errid);

/*
**	takes the command struct after
**	get_next_line put the raw input in command.input,
**	and splits it up into command.command, command.argc, and command.argv.
**	it also takes an env_list and puts it in char ** format in command.envp.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_split_command(t_env *env_list, t_command *command);

/*
**	Takes a command struct after get_next_line parsed the input,
**	and handles it accordingly with the provided env_list:
**	It splits it up into argc, argv, converts env_list to envp,
**	expands $ and ~, and runs the command.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_handle_command(t_env *env_list, t_command command);

/*
**	Takes a command (argv[0]) and checks if it is a builtin,
**	or if it can be found in PATH.
**	If it's a builtin, sets command.path to an empty string.
**	If it finds an executable, sets command.path to the absolute path.
**	if it can not be found, sets command.path to NULL.
**	Returns:
**	0 on succes.
**	- errid error code on failure.
*/
int						ft_find_executable(t_env *env_list, t_command *command);

/*
**	Takes argv after it had been split up by ft_split_command,
**	and expands any ~ or $.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_handle_expansions(t_env *env_list, char **argv);

/*
**	Takes a pointer to a string and the env list,
**	and expands the string correctly if it starts with ~ or $.
**	on succes, frees the old string and replaces it with the new one.
**	on failure, nothing is changed.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_expand_variable(t_env *env_list, char **string);

/*
**	Takes a pointer to a command struct, and frees everything in it.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_free_command(t_command *command);

/*
**	Takes a pointer to an environment list, and frees everything in it.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int						ft_free_env_list(t_env *env_list);

/*
**	Takes the name of a command(argv[0]) and checks if it is a builtin.
**	Returns:
**	0 on succes. (IS builtin)
**	-1 on failure. (is NOT builtin)
*/
int						ft_is_builtin(char *command);

#endif
