/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_expansions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 12:00:42 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 15:16:58 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_handle_expansions(t_env *env_list, char **argv)
{
	int index;
	int ret;
	int final_ret;

	index = 1;
	final_ret = 0;
	while (argv[index] != NULL)
	{
		if (argv[index][0] == '$' || argv[index][0] == '~')
		{
			ret = ft_expand_variable(env_list, &(argv[index]));
			if (ret != 0)
			{
				final_ret = ret;
			}
		}
		index++;
	}
	return (final_ret);
}
