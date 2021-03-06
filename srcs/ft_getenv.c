/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:49:17 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 21:37:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *env, const char *key)
{
	t_env *current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
