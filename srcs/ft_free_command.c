/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:10:47 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 15:26:27 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_free_command(t_command *command)
{
	size_t	index;

	index = 0;
	free(command->input);
	command->input = NULL;
	ft_free_str_array(command->argv);
	command->argv = NULL;
	ft_free_str_array(command->envp);
	command->envp = NULL;
	free(command->path);
	command->path = NULL;
	command->argc = 0;
	return (0);
}
