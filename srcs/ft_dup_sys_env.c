/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dup_sys_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/11 16:30:05 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_new_env_list_item(t_errid *errid, char *env_variable)
{
	t_env		*new;

	new = (t_env *)ft_memalloc(sizeof(t_env) * 1);
	if (new == NULL)
		*errid = ERR_MALLOCFAIL;
	else
	{
		new->key = ft_strcdup(env_variable, '=');
		new->value = ft_strdup(&(
	env_variable[ft_strlenc(env_variable, '=', ft_strlen(env_variable)) + 1]));
	}
	return (new);
}

t_env			*ft_dup_sys_env(t_errid *errid)
{
	extern char	**environ;
	size_t		index;
	t_env		*start;
	t_env		*current;

	index = 0;
	current = NULL;
	if (environ[index] != NULL)
	{
		current = ft_new_env_list_item(errid, environ[index]);
		if (current == NULL)
			return (NULL);
		index++;
	}
	start = current;
	while (environ[index] != NULL)
	{
		current->next = ft_new_env_list_item(errid, environ[index]);
		current = current->next;
		if (current == NULL)
			return (NULL);
		index++;
	}
	return (start);
}
