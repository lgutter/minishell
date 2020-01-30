/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_command.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:29:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:53:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_split_command(t_env *env_list, t_command *command)
{
	command->argv = NULL;
	command->path = NULL;
	command->envp = NULL;
	command->envp = ft_convert_env_to_envp(env_list);
	if (command->envp == NULL)
		return (ft_print_error(ERR_MALLOCFAIL));
	command->argv = ft_strsplit(command->input, ' ');
	if (command->argv == NULL)
		return (ft_print_error(ERR_MALLOCFAIL));
	command->argc = (int)ft_str_arr_len(command->argv);
	return (0);
}
