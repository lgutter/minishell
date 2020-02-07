/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo_builtin_tests.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 11:57:22 by lgutter       ########   odam.nl         */
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

Test(unit_ft_echo_builtin, basic_mandatory_empty_echo, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("echo");
	command.argv = ft_strsplit("echo", ' ');
	command.argc = 1;
	command.envp = NULL;
	ret = ft_echo_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("\n");
	cr_assert_eq(ret, 0);
	cr_assert_eq(env->next, NULL);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
}

Test(unit_ft_echo_builtin, basic_mandatory_simple_echo, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("echo foo");
	command.argv = ft_strsplit("echo foo", ' ');
	command.argc = 2;
	command.envp = NULL;
	ret = ft_echo_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("foo\n");
	cr_assert_eq(ret, 0);
	cr_assert_eq(env->next, NULL);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
}

Test(unit_ft_echo_builtin, basic_mandatory_simple_multiple_echo, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("echo foo bar baz");
	command.argv = ft_strsplit("echo foo bar baz", ' ');
	command.argc = 4;
	command.envp = NULL;
	ret = ft_echo_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("foo bar baz\n");
	cr_assert_eq(ret, 0);
	cr_assert_eq(env->next, NULL);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
}

Test(unit_ft_echo_builtin, basic_mandatory_error_argc_too_small, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("echo foo bar baz");
	command.argv = ft_strsplit("echo foo bar baz", ' ');
	command.argc = 2;
	command.envp = NULL;
	ret = ft_echo_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("foo\n");
	cr_assert_eq(ret, 1);
	cr_assert_eq(env->next, NULL);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
}

Test(unit_ft_echo_builtin, basic_mandatory_error_argc_too_big, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("");
	env->value = strdup("");
	env->next = NULL;
	command.input = strdup("echo foo bar baz");
	command.argv = ft_strsplit("echo foo bar baz", ' ');
	command.argc = 42;
	command.envp = NULL;
	ret = ft_echo_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("foo bar baz\n");
	cr_assert_eq(ret, 1);
	cr_assert_eq(env->next, NULL);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
}
