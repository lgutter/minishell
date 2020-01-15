/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getstatus_tests.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:20:03 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/15 12:34:18 by lgutter       ########   odam.nl         */
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

Test(unit_ft_getstatus, mandatory_basic_get_status_in_single_element_list)
{
	int		value;
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env) * 1);
	list->key = strdup(STATUS_CODE_KEY);
	list->value = strdup("1");
	value = ft_getstatus(list);
	cr_assert_eq(value, 1);
}

Test(unit_ft_getstatus, mandatory_basic_get_status_from_empty_list, .init = redirect_std_err)
{
	int value;
	t_env *list = NULL;

	value = ft_getstatus(list);
	fflush(stderr);
	cr_assert_eq(value, -1);
	cr_assert_stderr_eq_str("-ish: Environment key not found\n");
}

Test(unit_ft_getstatus, mandatory_basic_get_status_from_system_list, .init = redirect_std_err)
{
	int value;
	t_errid errid = 0;
	t_env *list;

	setenv(STATUS_CODE_KEY, "123", 1);
	list = ft_dup_sys_env(&errid);
	value = ft_getstatus(list);
	cr_assert_eq(value, 123);
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}
