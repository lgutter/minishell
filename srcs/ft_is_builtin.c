/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 12:46:00 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:09:08 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_builtin(char *command)
{
	if (ft_strcmp("echo", command) == 0)
		return (0);
	if (ft_strcmp("cd", command) == 0)
		return (0);
	if (ft_strcmp("setenv", command) == 0)
		return (0);
	if (ft_strcmp("unsetenv", command) == 0)
		return (0);
	if (ft_strcmp("env", command) == 0)
		return (0);
	if (ft_strcmp("exit", command) == 0)
		return (0);
	return (-1);
}
