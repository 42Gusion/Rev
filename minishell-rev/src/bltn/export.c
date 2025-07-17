/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:40:44 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:40:45 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	change_existing(t_env *change, char *str)
{
	size_t	pos;

	pos = msh_strlen(str, '=');
	while (change != NULL)
	{
		if (msh_strncmp(change->entry, str, pos) == 0)
			break ;
		change = change->next;
	}
	if (change == NULL)
		return (0);
	free(change->value);
	pos += 1;
	change->value = msh_strdup(&str[pos], msh_strlen(&str[pos], '\0'));
	if (!change->value)
		return (-1);
	return (1);
}

static int	name_invalid(char *str, t_env *envp)
{
	size_t	pos;
	int		err;

	if (str[0] != '_'
		&& !(str[0] >= 'A' && str[0] <= 'Z')
		&& !(str[0] >= 'a' && str[0] <= 'z'))
		return (1);
	pos = 1;
	while (str[pos] != '\0' && str[pos] != '='
		&& (str[pos] == '_' || msh_isalnum(str[pos])))
		pos++;
	if (str[pos] == '\0' || str[pos] != '=')
		return (1);
	err = change_existing(envp, str);
	if (err == -1)
		return (-1);
	else if (err == 1)
		return (2);
	return (0);
}

static int	export_print(t_env *envp)
{
	t_env	*print;

	print = envp->next;
	while (print != NULL)
	{
		msh_putstr("declare -x ", STDOUT_FILENO);
		msh_putstr(print->entry, STDOUT_FILENO);
		msh_putstr("=\"", STDOUT_FILENO);
		msh_putstr(print->value, STDOUT_FILENO);
		msh_putstr("\"\n", STDOUT_FILENO);
		print = print->next;
	}
	return (0);
}

static t_env	*last_env(t_env *envp)
{
	t_env	*last;

	last = envp->next;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	exec_export(char **args, t_env **envp)
{
	t_env	*hold;
	int		pos;
	int		ret;

	if (args[1] == NULL)
		return (export_print(*envp));
	hold = last_env(*envp);
	pos = 1;
	while (args[pos] != NULL)
	{
		ret = name_invalid(args[pos], *envp);
		if (ret == 1)
			msh_putstr("export: Invalid\n", STDERR_FILENO);
		if (ret == -1)
			return (EXIT_FAILURE);
		else if (ret == 0 && ret != 2)
		{
			hold->next = env_new(args[pos]);
			if (!hold->next)
				return (EXIT_FAILURE);
			hold = hold->next;
		}
		pos++;
	}
	return (EXIT_SUCCESS);
}
