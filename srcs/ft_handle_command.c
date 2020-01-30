/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:19:30 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:51:22 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command(t_env *env_list, t_command *command)
{
	int		stat_loc;
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(command->path, command->argv, command->envp);
		exit(ft_print_error(ERR_EXECVE_FAILED));
	}
	else if (pid > 0)
	{
		wait(&stat_loc);
		if (ft_setstatus(env_list, WEXITSTATUS(stat_loc)) != 0)
			ret = WEXITSTATUS(stat_loc);
	}
	else
	{
		ret = ft_print_error(ERR_FORK_FAILED);
	}
	return (ret);
}

int			ft_handle_command(t_env *env_list, t_command command)
{
	int ret;

	ret = ft_split_command(env_list, &command);
	if (ret == 0)
	{
		ret = ft_handle_expansions(env_list, command.argv);
		if (ret == 0)
		{
			ret = ft_find_executable(env_list, &command);
			if (ret == 0)
			{
				if (command.path[0] != '\0')
					ret = execute_command(env_list, &command);
				else
					ft_printf("detected builtin: %s\n", command.argv[0]);
			}
			else
			{
				ft_dprintf(2, "-ish: %s: command not found\n", command.argv[0]);
				ret = ERR_CMD_NOT_FOUND;
			}
		}
	}
	ft_free_command(&command);
	return (ret);
}
