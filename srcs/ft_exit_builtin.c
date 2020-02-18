/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:35:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 17:55:53 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	str_is_number(char *string)
{
	size_t index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] < '0' || string[index] > '9')
		{
			return (0);
		}
		index++;
	}
	return (1);
}

void		ft_exit_builtin(t_env *env_list, t_command *command)
{
	unsigned char	exit_code;
	char			*env_status;

	env_status = ft_getenv(env_list, STATUS_CODE_KEY);
	exit_code = 1;
	if (command->argc > 2)
		ft_dprintf(2, "exit: Too many arguments, extra arguments ignored.\n");
	if (command->argc >= 2)
	{
		if (str_is_number(command->argv[1]) == 1)
			exit_code = (unsigned char)ft_atoi(command->argv[1]);
		else
			ft_dprintf(2, "exit: First argument should be numeric.\n");
	}
	else if (env_status != NULL)
		exit_code = (unsigned char)ft_atoi(env_status);
	else
		exit_code = 0;
	ft_free_command(command);
	ft_free_env_list(env_list);
	ft_printf("exit\n");
	exit(exit_code);
}
