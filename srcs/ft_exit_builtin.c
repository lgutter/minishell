/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:35:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 10:41:57 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_exit_builtin(t_env *env_list, t_command *command)
{
	int		exit_code;
	char	*env_status;

	env_status = ft_getenv(env_list, STATUS_CODE_KEY);
	if (env_status == NULL)
	{
		exit_code = 0;
	}
	else
	{
		exit_code = ft_atoi(env_status);
	}
	ft_free_command(command);
	ft_free_env_list(env_list);
	ft_printf("exit\n");
	exit(exit_code);
}
