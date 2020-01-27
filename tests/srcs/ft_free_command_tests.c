/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_command_tests.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:14:25 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/22 15:28:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <string.h>
#include "minishell.h"

Test(unit_ft_free_command, basic_mandatory_free_short_command)
{
	t_command	command;
	int			ret;
	char		*teststring = "test command string";

	command.input = strdup(teststring);
	command.argc = 3;
	command.argv = ft_strsplit(command.input, ' ');
	command.envp = ft_strsplit("TEST=ONE FOO=BAR BAZ=OOF", ' ');
	cr_assert_neq(command.input, NULL);
	cr_assert_neq(command.argv, NULL);
	cr_assert_neq(command.envp, NULL);
	ret = ft_free_command(&command);
	cr_assert_eq(ret, 0);
	cr_assert_eq(command.input, NULL);
	cr_assert_eq(command.argv, NULL);
	cr_assert_eq(command.envp, NULL);
}
