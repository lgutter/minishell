/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:07 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/10 17:53:25 by lgutter       ########   odam.nl         */
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
		ft_print_error(&errid);
	while (1)
	{
		ft_printf(SHELL_PROMPT);
		get_next_line(0, &(command.input));
		ft_printf("you wrote: >%s<\n", command.input);
		if (ft_strcmp(command.input, "exit") == 0)
		{
			ft_dprintf(2, "exit\n");
			exit(0);
		}
		free(command.input);
	}
	return (0);
}
