/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_executable_tests.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 12:43:24 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:20:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "minishell.h"

Test(unit_ft_find_executable, basic_mandatory_find_printf)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/tmp/:/usr/bin");
	env->next = NULL;

	command.input = strdup("printf foo");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(command.path, "/usr/bin/printf");
}

Test(unit_ft_find_executable, basic_mandatory_find_cp)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->next = NULL;

	command.input = strdup("cp foo");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(command.path, "/bin/cp");
}

Test(unit_ft_find_executable, basic_mandatory_find_builtin)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->next = NULL;

	command.input = strdup("echo foo");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(command.path, "");
}

Test(unit_ft_find_executable, basic_mandatory_already_relative_path)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->next = NULL;

	command.input = strdup("./minishell foo");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(command.path, "./minishell");
}

Test(unit_ft_find_executable, basic_mandatory_already_absolute_path)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->next = NULL;

	command.input = strdup("/usr/bin/printf foo");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(command.path, "/usr/bin/printf");
}

Test(unit_ft_find_executable, basic_mandatory_error_nonexistent)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->next = NULL;

	command.input = strdup("foo bar");
	command.argc = 2;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = ft_find_executable(env, &command);
	cr_assert_neq(ret, 0);
	cr_assert_eq(command.path, NULL);
}
