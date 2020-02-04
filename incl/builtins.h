/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:00:17 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 14:49:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

/*
**	The builtin command cd will attemt to change the current directory.
**	This version of cd only accepts 1 argument.
**	If no argument is given, changes to the home directory.
**	If the first argument is "-", it will change to the path in OLDPWD,
**	or the home directory if OLDPWD is not set.
**	Otherwise it will attempt to change to the path that the argument contains.
**	If it fails, it will print an error message,
**	if it succeeds, it will print the new current directory.
**	Returns:
**	0 on succes.
**	1 on failure.
*/
int		ft_cd_builtin(t_env *env_list, t_command *command);

/*
**	The builtin command echo will print all its arguments,
**	seperated by spaces and followed by a newline character.
**	this version of echo does not accept any options.
**	Returns:
**	0 on succes.
**	1 on failure.
*/
int		ft_echo_builtin(t_env *env_list, t_command *command);

/*
**	The builtin command exit will properly exit the shell,
**	and print "exit" right before doing so.
**	It will use the most recent status code as exit code.
*/
int		ft_exit_builtin(t_env *env_list, t_command *command);

/*
**	The builtin command setenv will attempt to set the key-value pair
**	that is provided as arguments in the env_list and command->envp.
**	First argument should be a key, second argument the value.
**	If the key already exists, it will overwrite by default.
**	If no argument is given, it prints the environment.
**	Returns:
**	0 on succes.
**	1 on failure.
*/
int		ft_setenv_builtin(t_env *env_list, t_command *command);

/*
**	The builtin command unsetenv will attempt to remove the key-value pairs of
**	which the keys are provided as arguments in the env_list and command->envp.
**	if the key does not exists, does nothing.
**	If no argument is given, it prints an error.
**	Returns:
**	0 on succes.
**	1 on failure.
*/
int		ft_unsetenv_builtin(t_env *env_list, t_command *command);

/*
**	The builtin command env will print the current environment.
**	Returns:
**	0 on succes.
**	1 on failure.
*/
int		ft_env_builtin(t_env *env_list, t_command *command);

#endif
