/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_expansions_tests.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:33:58 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/07 08:45:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <string.h>
#include "minishell.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_handle_expansions, basic_mandatory_expand_only_tilde)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char **argv = ft_strsplit("hello ~ test", ' ');
	int ret;

	env->key = strdup("HOME");
	env->value = strdup("/home/criteriontest");
	env->next = NULL;
	ret = ft_handle_expansions(env, argv);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(argv[1], "/home/criteriontest");
}

Test(unit_ft_handle_expansions, basic_mandatory_expand_tilde_at_start)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char **argv = ft_strsplit("hello ~/test", ' ');
	int ret;

	env->key = strdup("HOME");
	env->value = strdup("/home/criteriontest");
	env->next = NULL;
	ret = ft_handle_expansions(env, argv);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(argv[1], "/home/criteriontest/test");
}

Test(unit_ft_handle_expansions, basic_error_expand_invalid_env_key, .init = redirect_std_err)
{
	t_errid errid;
	t_env *env = ft_dup_sys_env(&errid);
	char **argv = ft_strsplit("hello $doesnotexist test", ' ');
	int ret;

	ret = ft_handle_expansions(env, argv);
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
	cr_assert_eq(ret, 0);
}
