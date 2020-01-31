/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:08:52 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/31 15:35:08 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*find_path(t_env *env_list, t_command *command)
{
	char	*path;

	path = NULL;
	if (command->argc < 2)
		path = ft_getenv(env_list, "HOME");
	else if (command->argc == 2)
	{
		if (command->argv[1][0] == '-' && command->argv[1][1] == '\0')
		{
			path = ft_getenv(env_list, "OLDPWD");
			if (path == NULL)
				path = ft_getenv(env_list, "HOME");
		}
		else
			path = command->argv[1];
	}
	return (path);
}

int		ft_cd_builtin(t_env *env_list, t_command *command)
{
	char	*path;
	int		ret;

	ret = 0;
	path = find_path(env_list, command);
	if (path == NULL)
		return (ft_print_error(ERR_MALLOCFAIL));
	ret = chdir(path);
	if (ret != 0)
	{
		ft_dprintf(2, "cd: no such file or directory: %s\n", path);
		ft_setstatus(env_list, ret);
	}
	else
	{
		ft_printf("%s\n", path);
		ft_setenv(env_list, "OLDPWD", ft_getenv(env_list, "PWD"), 'y');
		path = NULL;
		path = getcwd(path, 1024);
		ft_setenv(env_list, "PWD", path, 'y');
		free(path);
	}
	return (ret);
}
