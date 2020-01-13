/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/11 20:10:09 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 16:56:24 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "minishell.h"

static void redirect_std_error(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_print_error, mandatory_basic_print_malloc_error, .init = redirect_std_error)
{
	t_errid errorcode = ERR_MALLOCFAIL;
	t_errid	errid = errorcode;
	int ret;

	ret = ft_print_error(errid);
	cr_assert_eq(errorcode, ret);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Failure to allocate memory\n");
}

Test(unit_ft_print_error, mandatory_basic_print_none_error, .init = redirect_std_error)
{
	t_errid errorcode = 0;
	t_errid	errid = errorcode;
	int ret;

	ret = ft_print_error(errid);
	cr_assert_eq(errorcode, ret);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Error state without error\n");
}

Test(unit_ft_print_error, mandatory_basic_print_unknown_error, .init = redirect_std_error)
{
	t_errid errorcode = 255;
	t_errid	errid = errorcode;
	int ret;

	ret = ft_print_error(errid);
	cr_assert_eq(errorcode, ret);
	fflush(stderr);
	cr_assert_stderr_eq_str("-ish: Invalid error code\n");
}


