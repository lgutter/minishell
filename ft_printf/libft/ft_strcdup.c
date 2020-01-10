/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:47:04 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/10 17:52:51 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *string, char delim)
{
	char	*ret;
	size_t	index;

	index = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlenc(string, delim) + 1));
	if (ret != NULL)
	{
		while (string[index] != delim)
		{
			ret[index] = string[index];
			index++;
		}
		ret[index] = '\0';
	}
	return (ret);
}
