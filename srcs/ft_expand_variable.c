/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand_variable.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 12:13:49 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 16:06:45 by lgutter       ########   odam.nl         */
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

	key = ft_strchr(*string, '$') + 1;
	ret = ft_strndup(*string, (key - *string - 1));
	len = ft_env_str_len(key);
	key = ft_strndup(key, len);
	if (ret == NULL || key == NULL)
	{
		free(ret);
		free(key);
		return (ERR_MALLOCFAIL);
	}
	ft_strexpand(&ret, ft_getenv(env_list, key));
	free(key);
	if (ret == NULL)
		return (ERR_MALLOCFAIL);
	ft_strexpand(&ret, ft_strchr(*string, '$') + len + 1);
	if (ret == NULL)
		return (ERR_MALLOCFAIL);
	free(*string);
	*string = ret;
	return (0);
}

int				ft_expand_variable(t_env *env_list, char **string)
{
	char	*temp;
	int		ret;

	ret = 0;
	temp = *string;
	if (temp[0] == '~' && (temp[1] == '\0' || temp[1] == '/'))
	{
		temp = ft_strjoin(ft_getenv(env_list, "HOME"), (temp + 1));
		if (temp == NULL)
			return (ERR_MALLOCFAIL);
		free(*string);
		*string = temp;
	}
	while (ft_strchr(*string, '$') != NULL &&
			ft_strchr(*string, '$') != &(*string)[ft_strlen(*string) - 1])
	{
		ret = ft_expand_dollar(env_list, string);
		if (ret != 0)
			break;
	}
	return (ret);
}
