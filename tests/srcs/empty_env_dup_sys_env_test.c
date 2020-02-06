/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   empty_env_dup_sys_env_test.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 19:32:02 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/06 20:01:41 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
**	This seperate test is needed because criterion is not able to
**	call a function after making the system env empty.
**	this main can be compiled with the following command:
**	"make MAIN=tests/srcs/empty_env_dup_sys_env_test.c CV=1 NAME=emptyenvtest",
**	and called with "env -i ./emptyenvtest".
**	that way, it is run with a completely empty environment.
*/

int main(void)
{
	t_env		*start_env;
	t_env		*current;
	t_errid		errid = 0;
	char		*realpwd;
	extern char **environ;

	start_env = ft_dup_sys_env(&errid);
	current = start_env;
	if (environ[0] != NULL)
	{
		dprintf(2, "Please run this test with env -i:\nenv -i ./emptyenvtest\n");
		return (1);
	}
	if (current == NULL || errid != 0)
	{
		dprintf(2, "ft_dup_sys_env did not exit correctly.\n");
		dprintf(2, "\treturn value:\t%p\n\terrid value:\t%hhu\n", current, errid);
		return (-1);
	}
	if (strcmp(current->key, "PWD") != 0)
	{
		dprintf(2, "incorrect key.\n\texpected:\tPWD\n\tactual:\t\t%s\n", current->key);
		return (-1);
	}
	realpwd = getcwd(NULL, 0);
	if (strcmp(current->value, realpwd) != 0)
	{
		dprintf(2, "incorrect value.\n\texpected:\t%s\n\tactual:\t\t%s\n", realpwd, current->value);
		free(realpwd);
		return (-1);
	}
	printf("Succesful empty env test!\n");
	free(realpwd);
	return (0);
}
