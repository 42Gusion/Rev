/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:08 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:09 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <sys/param.h>

static t_env	*last_env(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static int	exec_chdir(t_env **envp, const char *dir)
{
	t_env	*ptr;
	char	*new_cwd;

	new_cwd = malloc(sizeof(char) * MAXPATHLEN);
	if (!new_cwd)
		return (perror("cd: allocation"), EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		perror("cd");
		free(new_cwd);
		return (EXIT_FAILURE);
	}
	if (getcwd(new_cwd, MAXPATHLEN) == NULL)
	{
		perror("cd");
		free(new_cwd);
		return (EXIT_FAILURE);
	}
	ptr = last_env(*envp);
	return (cd_configure_env(envp, new_cwd, ptr));
}

int	exec_cd(char **args, t_env **envp)
{
	t_env	*home;
	t_env	*old;

	if (args[1] != NULL && args[2] != NULL)
		return (msh_putstr("cd: too many arguments\n", STDERR_FILENO),
			EXIT_FAILURE);
	home = env_fnd(*envp, "HOME");
	if (args[1] == NULL && !home)
		return (msh_putstr("cd: HOME not set\n", STDERR_FILENO),
			EXIT_FAILURE);
	else if (args[1] == NULL && home)
		return (exec_chdir(envp, home->next->value));
	old = env_fnd(*envp, "OLDPWD");
	if (args[1][0] == '-' && !old)
		return (msh_putstr("cd: OLDPWD not set\n", STDERR_FILENO),
			EXIT_FAILURE);
	else if (args[1][0] == '-' && old)
		return (exec_chdir(envp, old->next->value));
	return (exec_chdir(envp, args[1]));
}
