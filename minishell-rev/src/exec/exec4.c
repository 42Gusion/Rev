/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:14:58 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 05:17:20 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_path_next(const char *path_var, int *pos, const char *cmd)
{
	char	*path;
	int		len1;
	int		len2;

	len1 = msh_strlen(&path_var[*pos], ':');
	len2 = msh_strlen(cmd, '\0');
	path = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!path)
		return (*pos = -2, NULL);
	path[len1 + len2 + 1] = '\0';
	path[0] = '\0';
	msh_strncat(path, &path_var[*pos], len1);
	if (path_var[(*pos) + (len1 - 1)] != '/')
		msh_strncat(path, "/", 1);
	msh_strncat(path, cmd, len2);
	(*pos) += len1;
	if (path_var[*pos] == '\0')
		(*pos) = -1;
	else
		(*pos) += 1;
	return (path);
}

static int	try_external_loop(t_exec *ecfg, const char *path_var)
{
	int		pos;
	char	*path;

	if (!path_var)
		return (CMDNOTFND);
	else if (path_var[0] == '\0')
		return (CMDNOTFND);
	pos = 0;
	while (pos != -1 && pos != -2)
	{
		path = get_path_next(path_var, &pos, ecfg->argv[0]);
		if (!path)
			break ;
		if (execve(path, ecfg->argv, ecfg->envp) == -1)
			free(path);
	}
	if (pos == -2)
		return (FATALERROR);
	return (CMDNOTFND);
}

int	exec_command_external(t_exec *ecfg)
{
	t_env	*path_env;
	char	*path_var;
	int		found;

	if (msh_strchr(ecfg->argv[0], '/') == 1)
	{
		if (execve(ecfg->argv[0], ecfg->argv, ecfg->envp) == -1)
		{
			msh_putstr(ecfg->argv[0], STDERR_FILENO);
			msh_putstr(": command not found\n", STDERR_FILENO);
			return (CMDNOTFND);
		}
	}
	path_env = env_fnd(ecfg->shcfg->envl, "PATH");
	if (!path_env)
		return (msh_putstr("PATH is not set\n", STDERR_FILENO), CMDNOTFND);
	path_var = path_env->next->value;
	found = try_external_loop(ecfg, path_var);
	if (found == CMDNOTFND)
	{
		msh_putstr(ecfg->argv[0], STDERR_FILENO);
		msh_putstr(": command not found\n", STDERR_FILENO);
	}
	return (found);
}
