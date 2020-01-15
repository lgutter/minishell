/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:07 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/15 11:56:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	t_command	command;
	t_errid		errid;
	t_env		*env_start;

	env_start = ft_dup_sys_env(&errid);
	if (env_start == NULL)
		return (ft_print_error(errid));
	if (ft_setstatus(env_start, 0) != 0)
		return (ERR_MALLOCFAIL);
	while (1)
	{
		ft_printf(SHELL_PROMPT);
		get_next_line(0, &(command.input));
		free(command.input);
	}
	return (0);
}
