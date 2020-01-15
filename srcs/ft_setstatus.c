/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setstatus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 11:46:57 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/15 12:32:12 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_setstatus(t_env *env, int status)
{
	char	*status_str;
	int		ret;

	status_str = ft_itoa(status);
	if (status_str == NULL)
	{
		ft_print_error(ERR_MALLOCFAIL);
		return (-1);
	}
	ret = ft_setenv(env, STATUS_CODE_KEY, status_str, 'y');
	free(status_str);
	return (ret);
}
