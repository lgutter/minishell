/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env_builtin_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 12:12:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include "builtins.h"

static void redirect_std_out(void)
{
	cr_redirect_stdout();
}

Test(unit_ft_env_builtin, basic_mandatory_env_one_line, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("env");
	command.argv = ft_strsplit("env", ' ');
	command.argc = 1;
	command.envp = ft_strsplit("FOO=BAR", ' ');
	ret = ft_env_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("FOO=BAR\n");
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_env_builtin, basic_mandatory_env_3_lines, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("env");
	command.argv = ft_strsplit("env", ' ');
	command.argc = 1;
	command.envp = ft_strsplit("FOO=BAR BAZ=OOF CODAM=42", ' ');
	ret = ft_env_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("FOO=BAR\nBAZ=OOF\nCODAM=42\n");
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_env_builtin, basic_mandatory_error_NULL_envp, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("env");
	command.argv = ft_strsplit("env", ' ');
	command.argc = 1;
	command.envp = NULL;
	ret = ft_env_builtin(env, &command);
	printf("-");
	fflush(stdout);
	cr_assert_stdout_eq_str("-");
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
	cr_assert_eq(ret, 1);
}
