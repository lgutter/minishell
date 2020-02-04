/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_command_tests.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:58:45 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 13:47:02 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "minishell.h"

static void redirect_std_out(void)
{
	cr_redirect_stdout();
}

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_handle_command, basic_mandatory_handle_simple_command, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("TESTENVKEY");
	env->value = strdup("TESTENVVALUE");
	env->next = NULL;

	command.input = strdup("/bin/echo arg1 arg2 arg3");
	ret = ft_split_command(env, &command);
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("arg1 arg2 arg3\n");
}

Test(unit_ft_handle_command, basic_mandatory_handle_dollar_expansion_in_arg, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	t_env		*env2 = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("TESTENVKEY");
	env->value = strdup("TESTENVVALUE");
	env2->key = strdup("PATH");
	env2->value = strdup("foo:/bin:/usr/bin");
	env->next = env2;
	env2->next = NULL;


	command.input = strdup("printf %s\n $TESTENVKEY arg2");
	ret = ft_split_command(env, &command);
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("TESTENVVALUE\narg2\n");
}


Test(unit_ft_handle_command, basic_mandatory_handle_home_expansion_in_arg, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("HOME");
	env->value = strdup("/Users/lgutter");
	env->next = NULL;

	command.input = strdup("/bin/echo arg ~");
	ret = ft_split_command(env, &command);
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("arg /Users/lgutter\n");
}

Test(unit_ft_handle_command, basic_mandatory_error_command_not_found, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	t_env		*env_path = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("HOME");
	env->value = strdup("/Users/lgutter");
	env->next = env_path;
	env->key = strdup("PATH");
	env->value = strdup("/usr/bin");
	env->next = NULL;

	command.input = strdup("foobartest arg1 arg2");
	command.path = NULL;
	ret = ft_split_command(env, &command);
	ret = ft_handle_command(env, command);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: foobartest: command not found\n");
	cr_assert_eq(ret, ERR_CMD_NOT_FOUND);
}
