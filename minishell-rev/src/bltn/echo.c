/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:19 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:20 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	echo_n(char *arg)
{
	size_t	pos;

	pos = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[pos] != '\0' && arg[pos] == 'n')
		pos++;
	if (arg[pos] == '\0')
		return (1);
	return (0);
}

static void	echo_args(char **args, int pos)
{
	while (args[pos] != NULL)
	{
		msh_putstr(args[pos], STDOUT_FILENO);
		if (args[++pos] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
}

int	exec_echo(char **args, t_env **envp)
{
	int	nl;

	nl = 0;
	(void)envp;
	if (args[1] != NULL)
	{
		nl = echo_n(args[1]);
		if (nl)
			echo_args(args, 2);
		else
			echo_args(args, 1);
	}
	if (nl == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
