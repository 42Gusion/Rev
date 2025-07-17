/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:29 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:29 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cfg_curpwd(t_env *cur, t_env *old, t_env *last, char *new_cwd)
{
	(void)old;
	if (!cur)
	{
		last->next = env_new("PWD=");
		if (!last->next)
			return (1);
		cur = last->next;
		free(cur->value);
		cur->value = new_cwd;
	}
	else if (cur)
	{
		if (cur->next->value != NULL)
			free(cur->next->value);
		cur->next->value = new_cwd;
	}
	return (0);
}

static int	cfg_cdenv(t_env *cur, t_env *old, t_env *last, char *new_cwd)
{
	if (!old && cur)
	{
		last->next = env_new("OLDPWD=");
		if (!last->next)
			return (1);
		old = last->next;
		free(old->value);
		old->value = cur->next->value;
		cur->next->value = NULL;
	}
	else if (old && !cur)
	{
		free(old->next->value);
		old->next->value = msh_strdup("", 0);
		if (!old->value)
			return (1);
	}
	else if (old && cur)
	{
		free(old->next->value);
		old->next->value = cur->next->value;
		cur->next->value = NULL;
	}
	return (cfg_curpwd(cur, old, last, new_cwd));
}

int	cd_configure_env(t_env **envp, char *new_cwd, t_env *last)
{
	t_env	*curpwd;
	t_env	*oldpwd;
	int		stat;

	curpwd = env_fnd(*envp, "PWD");
	oldpwd = env_fnd(*envp, "OLDPWD");
	stat = cfg_cdenv(curpwd, oldpwd, last, new_cwd);
	if (stat == 1)
		free(new_cwd);
	return (stat);
}
