/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv_builtin_tests.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 13:17:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include "builtins.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_unsetenv_builtin, basic_mandatory_unsetenv_simple, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	t_env		*env2 = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = env2;
	env2->key = strdup("BAZ");
	env2->value = strdup("OOF");
	env2->next = NULL;
	command.input = strdup("unsetenv BAZ");
	command.argv = ft_strsplit("unsetenv BAZ", ' ');
	command.argc = 2;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_unsetenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_unsetenv_builtin, basic_mandatory_unsetenv_first, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	t_env		*env2 = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = env2;
	env2->key = strdup("BAZ");
	env2->value = strdup("OOF");
	env2->next = NULL;
	command.input = strdup("unsetenv FOO");
	command.argv = ft_strsplit("unsetenv FOO", ' ');
	command.argc = 2;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_unsetenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "BAZ");
	cr_assert_str_eq(env->value, "OOF");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_unsetenv_builtin, basic_mandatory_unsetenv_first_and_only, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("unsetenv FOO");
	command.argv = ft_strsplit("unsetenv FOO", ' ');
	command.argc = 2;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_unsetenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_unsetenv_builtin, basic_mandatory_unsetenv_fake_keys, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("unsetenv BLAH");
	command.argv = ft_strsplit("unsetenv BERP", ' ');
	command.argc = 2;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_unsetenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_unsetenv_builtin, basic_mandatory_error_no_args, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("unsetenv");
	command.argv = ft_strsplit("unsetenv", ' ');
	command.argc = 1;
	command.envp = NULL;
	ret = ft_unsetenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
	cr_assert_eq(ret, 1);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
	cr_assert_eq(env->next, NULL);
}
