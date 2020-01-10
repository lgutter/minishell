/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:37 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/10 18:14:20 by lgutter       ########   odam.nl         */
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
# define SHELL_PROMPT "\033[38;5;75m -ish > \033[0;00m"

/*
**	list of defines for errid.
*/
# define E_MALLOCFAIL 1

/*
**	typedef for our error tracking variable errid.
**	like the system errno, it contains a numerical error code.
**	Possible error codes are defined with the prefix 'ER_'.
*/
typedef int		t_errid;

/*
**	Struct to store info about the command to execute. Fields:
**	input:		the input as given by get_next_line.
**	command:	just the command (without args) extracted from input.
**	argc:		amount of arguments for command.
**	argv:		list of arguments for command, extracted from input.
*/
typedef struct	s_command
{
	char		*input;
	char		*command;
	int			argc;
	char		**argv;
}				t_command;

/*
**	Struct to store the environment variables in a linked list. Fields:
**	key:	The variable name. i.e. HOME
**	value:	The value of the variable. i.e. /Users/lgutter
**	next:	A pointer to the next element in the list of env variables
*/
typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

/*
**	converts the system char **environ to a linked list of our type t_env
**	returns the start of the list on succes, or NULL on failure.
**	(on failure, errid will be set to error code)
*/
t_env			*ft_dup_sys_env(t_errid *errid);

/*
**	takes the env and a key as argument and returns the value.
**	example: 'ft_getenv("PWD");' will return the path of our current directory.
**	when an error occurs, returns NULL.
**	(on failure, errid will be set to error code)
*/
char			*ft_getenv(t_env *env, const char *key);

/*
**	Takes env, a key, value, and either 'y' or 'n' as arguments.
**	If 'key' exists in env and 'overwrite' is 'y', overwrites the value.
**	If 'key' does not exist, adds it to env and sets the value.
**	Returns the following:
**	'0' on succes, '-1' on failure.
**	(on failure, errid will be set to error code)
*/
int				ft_setenv(t_env *env, const char *key, const char *value,
							char overwrite);

/*
**	takes env and a key as argument and removes it from our environment.
**	returns the following:
**	'0' on succes, '-1' on failure.
**	(on failure, errid will be set to error code)
*/
int				ft_unsetenv(t_env *env, const char *key);

/*
**	converts our linked list of type t_env to the the system style char **envp.
**	returns the an char ** on succes, or NULL on failure.
**	(on failure, errid will be set to error code)
*/
char			**ft_convert_env_to_envp(t_env **list_start);

/*
**	prints an error message relevant for the value of errid,
**	and resets errid to 0.
**	returns the previous value of errid.
*/
int				ft_print_error(t_errid *errid);

#endif
