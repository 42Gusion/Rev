/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:36 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:36 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_env(char **args, t_env **envp)
{
	t_env	*print;

	(void)args;
	print = (*envp)->next;
	while (print != NULL)
	{
		if (msh_putstr(print->entry, STDOUT_FILENO))
			return (EXIT_FAILURE);
		write(STDOUT_FILENO, "=", 1);
		if (msh_putstr(print->value, STDOUT_FILENO))
			return (EXIT_FAILURE);
		write(STDOUT_FILENO, "\n", 1);
		print = print->next;
	}
	return (EXIT_SUCCESS);
}
