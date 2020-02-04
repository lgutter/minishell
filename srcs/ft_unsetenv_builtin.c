/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:28:32 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 15:31:42 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	update_envp(t_command *command)
{
	size_t index;
	size_t unset_index;
	size_t len;

	index = 0;
	unset_index = 0;
	while (command->envp[index] != NULL)
	{
		len = ft_strlen(command->envp[index]);
		len = ft_strlenc(command->envp[index], '=', len);
		if (ft_strncmp(command->envp[index], command->argv[1], len) == 0)
		{
			unset_index = index;
			free(command->envp[unset_index]);
			break ;
		}
		index++;
	}
	if (command->envp[index] == NULL)
		return (1);
	while (command->envp[index + 1] != NULL)
		index++;
	command->envp[unset_index] = command->envp[index];
	command->envp[index] = NULL;
	return (0);
}

int			ft_unsetenv_builtin(t_env *env_list, t_command *command)
{
	int	ret;
	int	index;

	ret = 1;
	index = 1;
	if (command->argc < 2)
	{
		ft_dprintf(2, "unsetenv: Too few arguments.\n");
		return (ret);
	}
	while (index < command->argc && command->argv[index] != NULL)
	{
		if (ft_unsetenv(env_list, command->argv[index]) == 0)
		{
			update_envp(command);
		}
		index++;
	}
	return (0);
}
