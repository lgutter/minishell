/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:16:07 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 22:39:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_loop(t_env *env_start)
{
	t_command	command;
	int			ret;

	while (1)
	{
		ft_printf(SHELL_PROMPT);
		command.input = NULL;
		command.path = NULL;
		if (get_next_line(0, &(command.input)) == 0)
		{
			ret = ft_getstatus(env_start);
			ft_free_env_list(env_start);
			free(command.input);
			return (ret);
		}
		if (command.input[0] != '\0')
		{
			ret = ft_split_command(env_start, &command);
			if (ret == 0)
				ret = ft_handle_command(env_start, command);
		}
		else
			free(command.input);
	}
	return (ret);
}

static int	ft_set_sh_lvl(t_env *env_start)
{
	char	*value;
	int		level;
	int		ret;

	ret = ERR_MALLOCFAIL;
	value = ft_getenv(env_start, "SHLVL");
	if (value == NULL)
	{
		return (ft_setenv(env_start, "SHLVL", "1", 'y'));
	}
	else
	{
		level = ft_atoi(value);
		level++;
		value = ft_itoa(level);
		if (value != NULL)
		{
			ret = ft_setenv(env_start, "SHLVL", value, 'y');
		}
		free(value);
		return (ret);
	}
}

int			main(void)
{
	t_errid		errid;
	t_env		*env_start;
	int			ret;

	env_start = ft_dup_sys_env(&errid);
	if (env_start == NULL)
		return (ft_print_error(errid));
	ret = ft_setstatus(env_start, 0);
	ft_set_sh_lvl(env_start);
	if (ret != 0)
		return (ret);
	return (input_loop(env_start));
}
