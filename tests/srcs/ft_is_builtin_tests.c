/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_builtin_tests.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 15:19:49 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:23:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "minishell.h"

Test(unit_ft_is_builtin, basic_mandatory_find_echo)
{
	int			ret;
	ret = ft_is_builtin("echo");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_find_cd)
{
	int			ret;
	ret = ft_is_builtin("cd");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_find_setenv)
{
	int			ret;
	ret = ft_is_builtin("setenv");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_find_unsetenv)
{
	int			ret;
	ret = ft_is_builtin("unsetenv");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_find_env)
{
	int			ret;
	ret = ft_is_builtin("env");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_find_exit)
{
	int			ret;
	ret = ft_is_builtin("exit");
	cr_assert_eq(ret, 0);
}

Test(unit_ft_is_builtin, basic_mandatory_error_find_non_existent)
{
	int			ret;
	ret = ft_is_builtin("foo");
	cr_assert_eq(ret, -1);
}
