/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd_builtin_tests.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 11:14:39 by lgutter       ########   odam.nl         */
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

Test(unit_ft_cd_builtin, basic_mandatory_cd_to_root, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PWD");
	env->value = getcwd(NULL, 0);
	env->next = NULL;
	command.input = strdup("cd /");
	command.argv = ft_strsplit("cd /", ' ');
	command.argc = 2;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_cd_builtin(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(getcwd(NULL, 0), "/");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_cd_builtin, basic_mandatory_cd_to_home, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("HOME");
	env->value = strdup("/");
	env->next = NULL;
	command.input = strdup("cd");
	command.argv = ft_strsplit("cd", ' ');
	command.argc = 1;
	command.envp = NULL;
	dprintf(2, "-");
	ret = ft_cd_builtin(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(getcwd(NULL, 0), "/");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_cd_builtin, basic_mandatory_cd_to_oldpwd, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*firstdir = getcwd(NULL, 0);

	env->key = strdup("OLDPWD");
	env->value = strdup("/");
	env->next = NULL;
	command.input = strdup("cd -");
	command.argv = ft_strsplit("cd -", ' ');
	command.argc = 2;
	command.envp = NULL;
	ret = ft_cd_builtin(env, &command);
	fflush(stdout);
	cr_assert_stdout_eq_str("/\n");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(getcwd(NULL, 0), "/");
	cr_assert_str_eq(firstdir, env->value);
}

Test(unit_ft_cd_builtin, basic_mandatory_error_cd_no_oldpwd, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*firstdir = getcwd(NULL, 0);

	env->key = strdup("PWD");
	env->value = getcwd(NULL, 0);
	env->next = NULL;
	command.input = strdup("cd -");
	command.argv = ft_strsplit("cd -", ' ');
	command.argc = 2;
	command.envp = NULL;
	ret = ft_cd_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("cd: OLDPWD not set\n");
	cr_assert_eq(ret, ERR_ENVNOTFOUND);
	cr_assert_str_eq(firstdir, getcwd(NULL, 0));
	cr_assert_str_eq(firstdir, env->value);
}

Test(unit_ft_cd_builtin, basic_mandatory_error_cd_no_home, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*firstdir = getcwd(NULL, 0);

	env->key = strdup("PWD");
	env->value = getcwd(NULL, 0);
	env->next = NULL;
	command.input = strdup("cd");
	command.argv = ft_strsplit("cd", ' ');
	command.argc = 1;
	command.envp = NULL;
	ret = ft_cd_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("cd: HOME not set\n");
	cr_assert_eq(ret, ERR_ENVNOTFOUND);
	cr_assert_str_eq(firstdir, getcwd(NULL, 0));
	cr_assert_str_eq(firstdir, env->value);
}

Test(unit_ft_cd_builtin, basic_mandatory_error_cd_not_valid, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*firstdir = getcwd(NULL, 0);

	env->key = strdup("PWD");
	env->value = getcwd(NULL, 0);
	env->next = NULL;
	command.input = strdup("cd foobar");
	command.argv = ft_strsplit("cd foobar", ' ');
	command.argc = 2;
	command.envp = NULL;
	ret = ft_cd_builtin(env, &command);
	fflush(stderr);
	cr_assert_stderr_eq_str("cd: no such file or directory: foobar\n");
	cr_assert_neq(ret, 0);
	cr_assert_str_eq(firstdir, getcwd(NULL, 0));
	cr_assert_str_eq(firstdir, env->value);
}
