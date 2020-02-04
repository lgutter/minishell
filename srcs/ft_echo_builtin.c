/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:26:12 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 14:49:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_echo_builtin(t_env *env_list, t_command *command)
{
	int index;

	index = 1;
	if (command->argc < 2)
		ft_printf("\n");
	else
	{
		while (index < command->argc && command->argv[index] != NULL)
		{
			ft_printf("%s", command->argv[index]);
			index++;
			if (index < command->argc && command->argv[index] != NULL)
				ft_printf(" ");
			else
				ft_printf("\n");
		}
		if (index < command->argc || command->argv[index] != NULL)
		{
			ft_setstatus(env_list, 1);
			return (1);
		}
	}
	ft_setstatus(env_list, 0);
	return (0);
}
