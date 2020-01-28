/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:31:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/28 16:56:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*errid_to_str(t_errid errid)
{
	static const char *errors[ERR_COUNT] = {
		[ERR_NOERR]			= "Error state without error",
		[ERR_MALLOCFAIL]	= "Failure to allocate memory",
		[ERR_ACCESS]		= "Permission denied",
		[ERR_ENVNOWRITE]	= "Environment key exists and overwrite is off",
		[ERR_ENVNOTFOUND]	= "Environment key not found",
		[ERR_EMPTYENV]		= "Environment is empty",
		[ERR_INVALID_EXP]	= "Invalid expansion",
		[ERR_EXECVE_FAILED]	= "Failure in execve",
		[ERR_FORK_FAILED]	= "Failure in fork",
		[ERR_CMD_NOT_FOUND]	= "Command not found",
	};

	return (errors[errid]);
}

int					ft_print_error(t_errid errid)
{
	const char	*error;

	if (errid < ERR_COUNT)
	{
		error = errid_to_str(errid);
		ft_dprintf(2, "-ish: %s\n", error);
	}
	else
	{
		ft_dprintf(2, "-ish: %s\n", "Invalid error code");
	}
	return (errid);
}
