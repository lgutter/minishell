/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit_builtin_tests.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 12:10:34 by lgutter       ########   odam.nl         */
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

Test(unit_ft_exit_builtin, basic_mandatory_exit_42, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup(STATUS_CODE_KEY);
	env->value = strdup("42");
	env->next = NULL;
	command.input = strdup("exit");
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_exit_builtin(env, &command);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 42);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

Test(unit_ft_exit_builtin, basic_mandatory_error_no_exit_code, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	command.input = strdup("exit");
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_exit_builtin(env, &command);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 0);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

Test(unit_ft_exit_builtin, undefined_error_nothing_defined, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = NULL;

	command.input = NULL;
	command.argv = NULL;
	command.argc = 0;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_exit_builtin(env, &command);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 0);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}
