/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expand_variable_tests.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:28:21 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/22 15:33:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <string.h>
#include "minishell.h"

Test(unit_ft_expand_variable, basic_mandatory_expand_tilde)
{
	t_errid errid;
	t_env *env = ft_dup_sys_env(&errid);
	char *test_string = strdup("~");
	int ret;

	ret = ft_expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, getenv("HOME"));
}

Test(unit_ft_expand_variable, basic_mandatory_expand_HOME)
{
	t_errid errid;
	t_env *env = ft_dup_sys_env(&errid);
	char *test_string = strdup("$HOME");
	int ret;

	ret = ft_expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, getenv("HOME"));
}
