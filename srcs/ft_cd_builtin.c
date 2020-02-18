/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:08:52 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/10 16:44:56 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*find_path(t_env *env_list, t_command *command)
{
	char	*path;

	path = NULL;
	if (command->argc < 2)
	{
		path = ft_getenv(env_list, "HOME");
		if (path == NULL)
			ft_dprintf(2, "cd: HOME not set\n");
	}
	else if (command->argc == 2)
	{
		if (command->argv[1][0] == '-' && command->argv[1][1] == '\0')
		{
			path = ft_getenv(env_list, "OLDPWD");
			if (path == NULL)
				ft_dprintf(2, "cd: OLDPWD not set\n");
			else
				ft_printf("%s\n", path);
		}
		else
			path = command->argv[1];
	}
	return (path);
}

int			ft_cd_builtin(t_env *env_list, t_command *command)
{
	char	*path;
	char	*old_path;
	int		ret;

	ret = 0;
	path = find_path(env_list, command);
	if (path == NULL)
		return (ERR_ENVNOTFOUND);
	old_path = getcwd(NULL, 0);
	ret = chdir(path);
	ft_setstatus(env_list, ret);
	if (ret != 0)
		ft_dprintf(2, "cd: no such file or directory: %s\n", path);
	else
	{
		if (old_path != NULL)
			ft_setenv(env_list, "OLDPWD", old_path, 'y');
		path = getcwd(NULL, 0);
		if (path != NULL)
			ft_setenv(env_list, "PWD", path, 'y');
		free(path);
	}
	free(old_path);
	return (ret);
}
