/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand_variable.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 12:13:49 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 16:51:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_env_str_len(char *string)
{
	size_t	index;

	index = 0;
	while (string[index] == '_' ||
			(string[index] >= 'A' && string[index] <= 'Z') ||
			(string[index] >= 'a' && string[index] <= 'z') ||
			(string[index] >= '0' && string[index] <= '9'))
	{
		index++;
	}
	return (index);
}

static int		ft_expand_dollar(t_env *env_list, char **string)
{
	char	*key;
	char	*ret;
	size_t	len;

	key = (*string) + 1;
	len = ft_env_str_len(key);
	key = ft_strndup(key, len);
	if (key == NULL)
	{
		return (ERR_MALLOCFAIL);
	}
	ret = ft_getenv(env_list, key);
	if (ret == NULL)
	{
		free(key);
		return (ERR_INVALID_EXP);
	}
	free(key);
	free(*string);
	*string = ft_strdup(ret);
	return (0);
}

int				ft_expand_variable(t_env *env_list, char **string)
{
	char	*temp;
	int		ret;

	ret = ERR_INVALID_EXP;
	temp = *string;
	if (temp[0] == '~')
	{
		ret = 0;
		if (temp[1] == '\0' || (temp[1] == '/' && temp[2] == '\0'))
		{
			temp = ft_strdup(ft_getenv(env_list, "HOME"));
			if (temp != NULL)
			{
				free(*string);
				*string = temp;
			}
			else
				ret = ERR_MALLOCFAIL;
		}
	}
	else if (temp[0] == '$')
	{
		return (ft_expand_dollar(env_list, string));
	}
	return (ret);
}
