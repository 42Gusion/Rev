/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:41:02 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:41:03 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	unset_next(char *target, t_env *head)
{
	t_env	*prev;

	prev = env_fnd(head, target);
	if (!prev)
		return (1);
	env_del(prev->next, prev);
	return (0);
}

int	exec_unset(char **args, t_env **envp)
{
	int	pos;

	pos = 1;
	if (args[pos] == NULL)
		return (EXIT_SUCCESS);
	while (args[pos] != NULL)
	{
		unset_next(args[pos], *envp);
		pos++;
	}
	return (EXIT_SUCCESS);
}
