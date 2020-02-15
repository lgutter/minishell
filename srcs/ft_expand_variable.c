/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand_variable.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 12:13:49 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/15 13:50:20 by lgutter       ########   odam.nl         */
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

static void		ft_str_expand_triple(char **source, char *add1, char *add2)
{
	ft_strexpand(source, add1);
	if (*source == NULL)
		return ;
	ft_strexpand(source, add2);
}

static int		ft_expand_dollar(t_env *env_list, char **string, char **start)
{
	char	*key;
	char	*ret;
	char	*value;
	size_t	len;

	ret = ft_strndup(*string, (*start - *string));
	len = ft_env_str_len((*start) + 1);
	key = ft_strndup((*start) + 1, len);
	if (ret == NULL || key == NULL || len == 0)
	{
		free(ret);
		free(key);
		if (len == 0)
			(*start)++;
		return (len == 0 ? 0 : ERR_MALLOCFAIL);
	}
	value = ft_getenv(env_list, key);
	free(key);
	ft_str_expand_triple(&ret, value, (*start) + len + 1);
	if (ret == NULL)
		return (ERR_MALLOCFAIL);
	*start = ret + (*start - *string) + (ft_strlen(value));
	free(*string);
	*string = ret;
	return (0);
}

static int		ft_expand_home(t_env *env_list, char **string)
{
	char	*temp;
	char	*value;
	int		ret;

	ret = 0;
	temp = *string;
	if (temp[0] == '~' && (temp[1] == '\0' || temp[1] == '/'))
	{
		value = ft_getenv(env_list, "HOME");
		if (value != NULL)
		{
			temp = ft_strjoin(value, (temp + 1));
			if (temp == NULL)
				return (ERR_MALLOCFAIL);
			free(*string);
			*string = temp;
		}
	}
	return (ret);
}

int				ft_expand_variable(t_env *env_list, char **string)
{
	int		ret;
	char	*offset;

	ret = 0;
	if ((*string)[0] == '~' && ((*string)[1] == '\0' || (*string)[1] == '/'))
	{
		ret = ft_expand_home(env_list, string);
	}
	offset = ft_strchr(*string, '$');
	while (offset != NULL && offset != &(*string)[ft_strlen(*string) - 1])
	{
		ret = ft_expand_dollar(env_list, string, &offset);
		if (ret != 0)
			break ;
		offset = ft_strchr(offset, '$');
	}
	return (ret);
}
