/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:31:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 12:14:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*errid_to_str(t_errid errid)
{
	static const char *errors[ERR_COUNT] = {
		[ERR_NOERR]			= "Error state without error",
		[ERR_MALLOCFAIL]	= "Failure to allocate memory",
		[ERR_ACCESS]		= "Permission denied",
	};

	return (errors[errid]);
}

int			ft_print_error(t_errid *errid)
{
	int			ret;
	const char	*error;

	ret = (int)*errid;
	if (*errid < ERR_COUNT)
	{
		error = errid_to_str(*errid);
		ft_dprintf(2, "-ish: %s\n", error);
	}
	else
	{
		ft_dprintf(2, "-ish: %s\n", "Invalid error code");
	}
	*errid = 0;
	return (ret);
}
