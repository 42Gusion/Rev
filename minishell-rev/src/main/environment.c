/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:41:51 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:41:52 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env	*env_new(char *str);
void	env_clr(t_env *hold);
t_env	*env_fnd(t_env *hold, char *target);
void	env_del(t_env *hold, t_env *prev);
t_env	*env_cfg(char **env);

t_env	*env_new(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->entry = msh_strdup(str, msh_strlen(str, '='));
	if (!new->entry)
		return (free(new), NULL);
	str += (msh_strlen(str, '=') + 1);
	new->value = msh_strdup(str, msh_strlen(str, '\0'));
	if (!new->value)
		return (free(new->entry), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	env_clr(t_env *hold)
{
	t_env	*prev;

	while (hold != NULL)
	{
		prev = hold;
		hold = hold->next;
		if (prev->entry != NULL)
			free(prev->entry);
		if (prev->value != NULL)
			free(prev->value);
		free(prev);
	}
}

t_env	*env_fnd(t_env *hold, char *target)
{
	t_env	*check;

	check = hold;
	while (check->next != NULL)
	{
		if (msh_strcmp(check->next->entry, target) == 0)
			return (check);
		check = check->next;
	}
	return (NULL);
}

void	env_del(t_env *hold, t_env *prev)
{
	if (prev != NULL)
		prev->next = hold->next;
	if (hold->entry != NULL)
		free(hold->entry);
	if (hold->value != NULL)
		free(hold->value);
	free(hold);
}

t_env	*env_cfg(char **env)
{
	t_env	*head;
	t_env	*hold;
	int		pos;

	head = env_new("\0");
	hold = head;
	pos = 0;
	while (env[pos] != NULL)
	{
		hold->next = env_new(env[pos]);
		if (!hold->next)
			return (env_clr(head), NULL);
		hold = hold->next;
		pos++;
	}
	return (head);
}
