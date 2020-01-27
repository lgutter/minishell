/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_command_tests.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:58:45 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/27 11:31:53 by lgutter       ########   odam.nl         */
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

Test(unit_ft_split_command, basic_mandatory_handle_simple_command, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("TESTENVKEY");
	env->value = strdup("TESTENVVALUE");
	env->next = NULL;

	command.input = strdup("test arg1 arg2 arg3");
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("command: test\nargc: 4\nargv[0]: test\nargv[1]: arg1\nargv[2]: arg2\nargv[3]: arg3\n");
}

Test(unit_ft_split_command, basic_mandatory_handle_dollar_expansion_in_arg, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("TESTENVKEY");
	env->value = strdup("TESTENVVALUE");
	env->next = NULL;

	command.input = strdup("test $TESTENVKEY arg2 arg3");
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("command: test\nargc: 4\nargv[0]: test\nargv[1]: TESTENVVALUE\nargv[2]: arg2\nargv[3]: arg3\n");
}

Test(unit_ft_split_command, basic_mandatory_handle_home_expansion_in_arg, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("HOME");
	env->value = strdup("/Users/lgutter");
	env->next = NULL;

	command.input = strdup("test ~ arg2 arg3");
	ret = ft_handle_command(env, command);
	fflush(stdout);
	cr_assert_eq(ret, 0);
	cr_assert_stdout_eq_str("command: test\nargc: 4\nargv[0]: test\nargv[1]: /Users/lgutter\nargv[2]: arg2\nargv[3]: arg3\n");
}

