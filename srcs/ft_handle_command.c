/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:19:30 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/22 14:33:40 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_handle_command(t_env *env_list, t_command command)
{
	int ret;

	ret = ft_split_command(env_list, &command);
	if (ret == 0)
	{
		ret = ft_handle_expansions(env_list, command.argv);
		if (ret == 0)
		{
			ft_printf("command: %s\n", command.argv[0]);
			ret = 0;
			ft_printf("argc: %i\n", command.argc);
			while (ret < command.argc)
			{
				ft_printf("argv[%i]: %s\n", ret, command.argv[ret]);
				ret++;
			}
			ret = ft_free_command(&command);
		}
	}
	return (ret);
}
