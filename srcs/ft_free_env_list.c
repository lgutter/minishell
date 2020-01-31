/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_env_list.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 14:01:30 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 14:03:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_free_env_list(t_env *env_list)
{
	t_env *current;
	t_env * previous;

	current = env_list;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	return (0);
}
