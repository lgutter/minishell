/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_command.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:29:22 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 16:47:41 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_split_command(t_env *env_list, t_command *command)
{
	char	*temp;
	int		ret;

	ret = 0;
	temp = ft_strtrim(command->input);
	if (temp[0] != '\0')
	{
		command->argv = ft_strsplit(temp, ' ');
		if (command->argv != NULL)
		{
			command->envp = ft_convert_env_to_envp(env_list);
			if (command->envp != NULL)
				command->argc = (int)ft_str_arr_len(command->argv);
			else
				ret = ERR_MALLOCFAIL;
		}
		else
			ret = ERR_MALLOCFAIL;
	}
	else
		ret = ERR_CMD_NOT_FOUND;
	free(temp);
	if (ret != 0)
		free(command->input);
	return (ret);
}
