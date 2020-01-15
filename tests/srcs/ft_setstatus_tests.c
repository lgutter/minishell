/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setstatus_tests.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 12:27:13 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/15 12:33:55 by lgutter       ########   odam.nl         */
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

Test(unit_ft_setstatus, mandatory_basic_set_new_simple, .init = redirect_std_err)
{
	int ret;
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	ret = ft_setstatus(env, 42);
	cr_assert_eq(ret, 0);
	env = env->next;
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "42");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setstatus, mandatory_basic_set_new_empty_first_element, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *second;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	second = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("");
	env->value = strdup("");
	env->next = second;
	second->key = strdup("FOO");
	second->value = strdup("BAR");
	second->next = NULL;
	ret = ft_setstatus(env, 24);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, STATUS_CODE_KEY);
	cr_assert_str_eq(env->value, "24");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setstatus, mandatory_basic_set_new_full_list, .init = redirect_std_err)
{
	int ret;
	t_errid errid;
	t_env *env;
	t_env *current;

	env = ft_dup_sys_env(&errid);
	current = env;
	ret = ft_setstatus(env, 142);
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, STATUS_CODE_KEY) == 0)
		{
			cr_assert_str_eq(current->value, "142");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setstatus, mandatory_basic_overwrite_in_full_list, .init = redirect_std_err)
{
	int ret;
	t_errid errid;
	t_env *env;
	t_env *current;

	setenv(STATUS_CODE_KEY, "0", 0);
	env = ft_dup_sys_env(&errid);
	current = env;
	ret = ft_setstatus(env, 42);
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, STATUS_CODE_KEY) == 0)
		{
			cr_assert_str_eq(current->value, "42");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setstatus, mandatory_error_empty_list, .init = redirect_std_err)
{
	int ret;
	t_env *env = NULL;

	ret = ft_setstatus(env, 42);
	cr_assert_eq(ret, ERR_EMPTYENV);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Environment is empty\n");
}
