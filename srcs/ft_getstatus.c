/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getstatus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 11:51:16 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/15 12:23:09 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_getstatus(t_env *env)
{
	char	*str_status_code;
	int		int_status_code;

	str_status_code = ft_getenv(env, STATUS_CODE_KEY);
	if (str_status_code == NULL)
		return (-1);
	int_status_code = ft_atoi(str_status_code);
	return (int_status_code);
}
