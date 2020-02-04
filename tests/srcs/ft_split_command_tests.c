/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_command_tests.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 10:58:45 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 13:04:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <string.h>
#include "minishell.h"

Test(unit_ft_split_command, basic_mandatory_split_simple_command)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("TESTENVKEY");
	env->value = strdup("TESTENVVALUE");
	env->next = NULL;

	command.input = strdup("test arg1 arg2 arg3");
	command.path = NULL;
	ret = ft_split_command(env, &command);
	cr_assert_eq(ret, 0);
	cr_assert_eq(command.argc, 4);
	cr_assert_str_eq(command.argv[0], "test");
	cr_assert_str_eq(command.argv[1], "arg1");
	cr_assert_str_eq(command.argv[2], "arg2");
	cr_assert_str_eq(command.argv[3], "arg3");
	cr_assert_str_eq(command.envp[0], "TESTENVKEY=TESTENVVALUE");
	cr_assert_eq(command.envp[1], NULL);
	cr_assert_eq(command.path, NULL);
}
