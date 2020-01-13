/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv_tests.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 17:00:36 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 17:13:49 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "minishell.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_getenv, mandatory_basic_get_valid_value_in_single_element_list)
{
	char *value;
	t_env *list;

	list = (t_env *)malloc(sizeof(t_env) * 1);
	list->key = strdup("MINISHELL_TEST_GET_ENV");
	list->value = strdup("VALUE_FOR_TEST_1");
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV");
	cr_assert_str_eq(value, "VALUE_FOR_TEST_1");
}

Test(unit_ft_getenv, mandatory_basic_get_from_empty_list, .init = redirect_std_err)
{
	char *value;
	t_env *list = NULL;

	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV");
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Environment key not found\n");
}

Test(unit_ft_getenv, mandatory_basic_get_valid_value_from_system_list, .init = redirect_std_err)
{
	char *value;
	t_errid errid = 0;
	t_env *list;

	setenv("MINISHELL_TEST_GET_ENV", "VALUE_FOR_TEST_3", 1);
	list = ft_dup_sys_env(&errid);
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV");
	cr_assert_str_eq(value, "VALUE_FOR_TEST_3");
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}
