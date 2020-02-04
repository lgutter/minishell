/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:42 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 15:05:22 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ft_env_builtin(t_env *env_list, t_command *command)
{
	int ret;

	ret = ft_print_str_array(command->envp);
	if (ret == -1)
		ret = 1;
	ft_setstatus(env_list, ret);
	return (ret);
}
