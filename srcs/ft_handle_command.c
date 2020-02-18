/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:19:30 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 17:57:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

static int	execute_builtin(t_env *env_list, t_command *command)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(command->argv[0], "cd") == 0)
		ret = ft_cd_builtin(env_list, command);
	else if (ft_strcmp(command->argv[0], "echo") == 0)
		ret = ft_echo_builtin(env_list, command);
	else if (ft_strcmp(command->argv[0], "exit") == 0)
		ft_exit_builtin(env_list, command);
	else if (ft_strcmp(command->argv[0], "env") == 0)
		ret = ft_env_builtin(env_list, command);
	else if (ft_strcmp(command->argv[0], "setenv") == 0)
		ret = ft_setenv_builtin(env_list, command);
	else if (ft_strcmp(command->argv[0], "unsetenv") == 0)
		ret = ft_unsetenv_builtin(env_list, command);
	return (ret);
}

int			ft_handle_command(t_env *env_list, t_command command)
{
	int ret;

	ret = ft_handle_expansions(env_list, command.argv);
	if (ret == 0)
	{
		ret = ft_find_executable(env_list, &command);
		if (ret == 0)
		{
			if (command.path[0] != '\0')
				ret = execute_command(env_list, &command);
			else
				ret = execute_builtin(env_list, &command);
		}
		else
		{
			ft_dprintf(2, "-ish: %s: command not found\n", command.argv[0]);
			ft_setstatus(env_list, ERR_CMD_NOT_FOUND);
			ret = ERR_CMD_NOT_FOUND;
		}
	}
	ft_free_command(&command);
	return (ret);
}
