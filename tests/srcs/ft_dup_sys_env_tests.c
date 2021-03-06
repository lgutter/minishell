/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dup_sys_env_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/11 14:19:16 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/13 15:44:58 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include "minishell.h"

Test(unit_ft_dup_sys_env, mandatory_basic_convert_sys_environ)
{
	t_env	*start_env;
	t_env	*current;
	t_errid	errid = 0;

	setenv("MINISHELLENVTEST", "TESTVALUEOFENVVAR", 1);
	setenv("MINISHELLENVTESTEMPTY", "", 1);
	start_env = ft_dup_sys_env(&errid);
	current = start_env;
	while (current != NULL)
	{
		cr_assert_str_not_empty(current->key);
		cr_assert_neq(current->value, NULL);
		if (strcmp(current->key, "MINISHELLENVTEST") == 0)
			cr_assert_str_eq(current->value, "TESTVALUEOFENVVAR");
		current = current->next;
	}
	cr_assert_eq(errid, 0);
}

Test(unit_ft_dup_sys_env, mandatory_basic_free_every_element)
{
	t_env	*start_env;
	t_env	*current;
	t_env	*old;
	t_errid	errid = 0;


	start_env = ft_dup_sys_env(&errid);
	current = start_env;
	while (current != NULL)
	{
		free(current->key);
		free(current->value);
		old = current;
		current = current->next;
		free(old);
	}
	cr_assert_eq(errid, 0);
}
