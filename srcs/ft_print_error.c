/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:31:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/10 17:34:36 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_error(t_errid *errid)
{
	int	ret;

	ret = (int)*errid;
	ft_dprintf(2, "-ish: %i", (int)*errid);
	*errid = 0;
	return (ret);
}
