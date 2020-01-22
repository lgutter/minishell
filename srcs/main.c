/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:07 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/22 14:35:36 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	t_command	command;
	t_errid		errid;
	t_env		*env_start;
	int			ret;

	env_start = ft_dup_sys_env(&errid);
	if (env_start == NULL)
		return (ft_print_error(errid));
	ret = ft_setstatus(env_start, 0);
	if (ret != 0)
		return (ret);
	while (1)
	{
		ft_printf(SHELL_PROMPT);
		if (get_next_line(0, &(command.input)) == 0)
		{
			ret = ft_getstatus(env_start);
			if (ret == 0)
				ret = -1;
			return (ret);
		}
		ret = ft_handle_command(env_start, command);
	}
	return (0);
}
