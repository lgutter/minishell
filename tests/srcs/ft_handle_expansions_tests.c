/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_expansions_tests.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:33:58 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/04 16:08:13 by lgutter       ########   odam.nl         */
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
		t_errid errid;
	t_env *env = ft_dup_sys_env(&errid);
	char **argv = ft_strsplit("hello ~ test", ' ');
	int ret;

	ret = ft_handle_expansions(env, argv);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(argv[1], getenv("HOME"));
}

Test(unit_ft_handle_expansions, basic_error_expand_invalid_env_key, .init = redirect_std_err)
{
		t_errid errid;
	t_env *env = ft_dup_sys_env(&errid);
	char **argv = ft_strsplit("hello $doesnotexist test", ' ');
	int ret;

	ret = ft_handle_expansions(env, argv);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Environment key not found\n");
	cr_assert_eq(ret, 0);
}
