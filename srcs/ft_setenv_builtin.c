/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:48:05 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 12:39:29 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_key(char *key)
{
	size_t	index;

	index = 0;
	if (ft_isalpha(key[0]) != 1 && key[0] != '_')
	{
		ft_dprintf(2, "setenv: Variable name must begin with ");
		ft_dprintf(2, "a letter or underscore.\n");
		return (1);
	}
	else
	{
		while (key[index] != '\0')
		{
			if (key[index] != '_' && ft_isalnum(key[index]) == 0)
			{
				ft_dprintf(2, "setenv: Variable name must only contain ");
				ft_dprintf(2, "alphanumerical characters.\n");
				return (1);
			}
			index++;
		}
	}
	return (0);
}

int			ft_setenv_builtin(t_env *env_list, t_command *command)
{
	int		ret;
	char	*value;

	ret = 1;
	value = command->argv[2];
	if (value == NULL)
		value = "";
	if (command->argc < 2)
		ret = ft_print_str_array(command->envp);
	else if (command->argc > 3)
		ft_dprintf(2, "setenv: Too many arguments.\n");
	else
	{
		ret = check_key(command->argv[1]);
		if (ret == 0)
		{
			ret = ft_setenv(env_list, command->argv[1], value, 'y');
		}
	}
	ft_setstatus(env_list, ret);
	return (ret);
}
