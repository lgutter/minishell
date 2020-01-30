/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_executable.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:34:10 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:08:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_exec_in_dir(char *dirname, char *exec_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dirname);
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, exec_name) == 0)
		{
			(void)closedir(dir);
			return (0);
		}
		entry = readdir(dir);
	}
	(void)closedir(dir);
	return (-1);
}

static int	ft_traverse_paths(char **paths, t_command *command)
{
	size_t	index;

	index = 0;
	while (paths[index] != NULL)
	{
		command->path = NULL;
		if (ft_find_exec_in_dir(paths[index], command->argv[0]) == 0)
		{
			if (paths[index][ft_strlen(paths[index]) - 1] != '/')
				ft_strexpand(&(paths[index]), "/");
			command->path = ft_strjoin(paths[index], command->argv[0]);
			if (command->path == NULL)
				return (ERR_MALLOCFAIL);
			else if (access(command->path, X_OK) == 0)
				return (0);
			else
				free(command->path);
		}
		index++;
	}
	return (-1);
}

int			ft_find_executable(t_env *env_list, t_command *command)
{
	char	*env_path;
	char	**paths;
	int		ret;

	ret = 0;
	if (ft_is_builtin(command->argv[0]) == 0)
	{
		command->path = ft_strdup("");
	}
	else if (ft_strchr(command->argv[0], '/') != NULL)
	{
		command->path = ft_strdup(command->argv[0]);
	}
	else
	{
		env_path = ft_getenv(env_list, "PATH");
		if (env_path == NULL)
			return (ERR_ENVNOTFOUND);
		paths = ft_strsplit(env_path, ':');
		if (paths == NULL)
			return (ft_print_error(ERR_MALLOCFAIL));
		ret = ft_traverse_paths(paths, command);
		ft_free_str_array(paths);
	}
	return (ret);
}
