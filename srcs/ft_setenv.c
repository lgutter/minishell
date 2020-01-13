/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 16:03:54 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 17:23:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_addenv(t_env *env, const char *key, const char *value)
{
	t_env *current;
	t_env *new;

	current = env;
	if (current == NULL)
	{
		return (ft_print_error(ERR_EMPTYENV));
	}
	new = (t_env *)ft_memalloc(sizeof(t_env) * 1);
	if (new == NULL)
	{
		return (ft_print_error(ERR_MALLOCFAIL));
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->key == NULL || new->value == NULL)
	{
		return (ft_print_error(ERR_MALLOCFAIL));
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return (0);
}

int			ft_setenv(t_env *env, const char *key,
										const char *value, char overwrite)
{
	t_env *current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (overwrite == 'y')
			{
				free(current->value);
				current->value = ft_strdup(value);
				if (current->value == NULL)
				{
					return (ft_print_error(ERR_MALLOCFAIL));
				}
				return (0);
			}
			return (ft_print_error(ERR_ENVNOWRITE));
		}
		current = current->next;
	}
	return (ft_addenv(env, key, value));
}
