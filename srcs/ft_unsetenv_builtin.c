/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:28:32 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 13:06:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ft_unsetenv_builtin(t_env *env_list, t_command *command)
{
	int	index;
	int	ret;

	index = 1;
	if (command->argc < 2)
	{
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
		ret = 1;
	}
	else
	{
		while (index < command->argc && command->argv[index] != NULL)
		{
			ft_unsetenv(env_list, command->argv[index]);
			index++;
		}
		ret = 0;
	}
	ft_setstatus(env_list, ret);
	return (ret);
}
