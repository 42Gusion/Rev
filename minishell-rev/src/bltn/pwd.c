/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:55 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:56 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_pwd(char **args, t_env **envp)
{
	char	*str;

	((void)args, (void)envp);
	str = malloc(sizeof(char) * MAXPATHLEN);
	if (!str)
		return (EXIT_FAILURE);
	if (getcwd(str, MAXPATHLEN) == NULL)
		return (free(str), EXIT_FAILURE);
	msh_putstr(str, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(str);
	return (EXIT_SUCCESS);
}
