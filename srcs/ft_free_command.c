/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:10:47 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/22 14:19:36 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_free_command(t_command *command)
{
	size_t	index;

	index = 0;
	free(command->input);
	ft_free_str_array(command->argv);
	ft_free_str_array(command->envp);
	return (0);
}
