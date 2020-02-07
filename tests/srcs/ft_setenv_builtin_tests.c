/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv_builtin_tests.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 12:40:36 by lgutter       ########   odam.nl         */
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

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_setenv_builtin, basic_mandatory_set_new_env, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv CODAM BAZ");
	command.argv = ft_strsplit("setenv CODAM BAZ", ' ');
	command.argc = 3;
	command.envp = NULL;
	printf("-");
	ret = ft_setenv_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, "CODAM");
	cr_assert_str_eq(env->value, "BAZ");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_setenv_builtin, basic_mandatory_replace_env, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv FOO BAZ");
	command.argv = ft_strsplit("setenv FOO BAZ", ' ');
	command.argc = 3;
	command.envp = NULL;
	printf("-");
	ret = ft_setenv_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("-");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAZ");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_setenv_builtin, basic_mandatory_no_args, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv");
	command.argv = ft_strsplit("setenv", ' ');
	command.argc = 1;
	command.envp = ft_strsplit("FOO=BAR FOR=BAO", ' ');
	ret = ft_setenv_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("FOO=BAR\nFOR=BAO\n");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "0");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_setenv_builtin, basic_mandatory_error_too_many_args, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv FOO BAR BAZ");
	command.argv = ft_strsplit("setenv FOO BAR BAZ", ' ');
	command.argc = 4;
	command.envp = NULL;
	ret = ft_setenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
	cr_assert_eq(ret, 1);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_setenv_builtin, basic_mandatory_error_invalid_key_digit_start, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv 3FOO BAR");
	command.argv = ft_strsplit("setenv 3FOO BAR", ' ');
	command.argc = 3;
	command.envp = NULL;
	ret = ft_setenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
	cr_assert_eq(ret, 1);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
	cr_assert_eq(env->next, NULL);
}

Test(unit_ft_setenv_builtin, basic_mandatory_error_invalid_key_invalid_char, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("setenv FO*O BAR");
	command.argv = ft_strsplit("setenv FO*O BAR", ' ');
	command.argc = 3;
	command.envp = NULL;
	ret = ft_setenv_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("setenv: Variable name must only contain alphanumerical characters.\n");
	cr_assert_eq(ret, 1);
	cr_assert_str_eq(env->key, "FOO");
	cr_assert_str_eq(env->value, "BAR");
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "1");
	cr_assert_eq(env->next, NULL);
}
