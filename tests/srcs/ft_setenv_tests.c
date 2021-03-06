/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv_tests.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 17:15:37 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 21:10:52 by lgutter       ########   odam.nl         */
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

Test(unit_ft_setenv, mandatory_basic_set_new_simple, .init = redirect_std_err)
{
	int ret;
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	ret = ft_setenv(env, "TEST_KEY", "TEST_VALUE", 'n');
	cr_assert_eq(ret, 0);
	env = env->next;
	cr_assert_str_eq(env->key, "TEST_KEY");
	cr_assert_str_eq(env->value, "TEST_VALUE");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_set_new_empty_first_element, .init = redirect_std_err)
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
	ret = ft_setenv(env, "TEST_KEY", "TEST_VALUE", 'n');
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "TEST_KEY");
	cr_assert_str_eq(env->value, "TEST_VALUE");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_set_new_full_list, .init = redirect_std_err)
{
	int ret;
	t_errid errid;
	t_env *env;
	t_env *current;

	env = ft_dup_sys_env(&errid);
	current = env;
	ret = ft_setenv(env, "MINISHELL_TEST_KEY", "TEST_VALUE", 'n');
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, "MINISHELL_TEST_KEY") == 0)
		{
			cr_assert_str_eq(current->value, "TEST_VALUE");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_overwrite_in_full_list, .init = redirect_std_err)
{
	int ret;
	t_errid errid;
	t_env *env;
	t_env *current;

	setenv("MINISHELL_TEST_KEY", "FIRST_TEST_VALUE", 1);
	env = ft_dup_sys_env(&errid);
	current = env;
	ret = ft_setenv(env, "MINISHELL_TEST_KEY", "TEST_VALUE_NEW", 'y');
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, "MINISHELL_TEST_KEY") == 0)
		{
			cr_assert_str_eq(current->value, "TEST_VALUE_NEW");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_error_deny_overwrite_in_full_list, .init = redirect_std_err)
{
	int ret;
	t_errid errid;
	t_env *env;
	t_env *current;

	setenv("MINISHELL_TEST_KEY", "FIRST_TEST_VALUE", 1);
	env = ft_dup_sys_env(&errid);
	current = env;
	ret = ft_setenv(env, "MINISHELL_TEST_KEY", "TEST_VALUE_NEW", 'n');
	cr_assert_eq(ret, ERR_ENVNOWRITE);
	while (current != NULL)
	{
		if (strcmp(current->key, "MINISHELL_TEST_KEY") == 0)
		{
			cr_assert_str_eq(current->value, "FIRST_TEST_VALUE");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Environment key exists and overwrite is off\n");
}

Test(unit_ft_setenv, mandatory_error_empty_list, .init = redirect_std_err)
{
	int ret;
	t_env *env = NULL;

	ret = ft_setenv(env, "MINISHELL_TEST_KEY", "TEST_VALUE_NEW", 'n');
	cr_assert_eq(ret, ERR_EMPTYENV);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Environment is empty\n");
}
