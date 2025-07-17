/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:08:01 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 01:10:45 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_strarr(char **arr)
{
	int	count;

	count = 0;
	while (arr[count] != NULL)
		free(arr[count++]);
	free(arr);
}

static int	argenv_counter(t_list *p1, t_env *p2)
{
	int	count;

	count = 0;
	if (p1 != NULL && p2 == NULL)
	{
		while (p1 != NULL)
		{
			p1 = p1->next;
			count++;
		}
	}
	else if (p1 == NULL && p2 != NULL)
	{
		while (p2 != NULL)
		{
			p2 = p2->next;
			count++;
		}
	}
	return (count);
}

char	**create_argv(t_list *args)
{
	char	**ret;
	t_list	*ptr;
	int		count;

	count = argenv_counter(args, NULL);
	ptr = args;
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = NULL;
	count = 0;
	ptr = args;
	while (ptr != NULL)
	{
		ret[count] = msh_strdup(ptr->entry, msh_strlen(ptr->entry, '\0'));
		if (!ret[count])
			return (free_strarr(ret), NULL);
		ptr = ptr->next;
		count++;
	}
	return (ret);
}

static char	*mkenv_full(const char *key, const char *value)
{
	char	*new;
	size_t	len;

	len = msh_strlen(key, '\0');
	len += msh_strlen(value, '\0');
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	new[0] = '\0';
	msh_strcat(new, key);
	msh_strcat(new, "=");
	msh_strcat(new, value);
	return (new);
}

char	**create_envp(t_env *envl)
{
	char	**ret;
	t_env	*ptr;
	int		count;

	count = argenv_counter(NULL, envl->next);
	ptr = envl->next;
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = NULL;
	count = 0;
	ptr = envl->next;
	while (ptr != NULL)
	{
		ret[count] = mkenv_full(ptr->entry, ptr->value);
		if (!ret[count])
			return (free_strarr(ret), NULL);
		ptr = ptr->next;
		count++;
	}
	return (ret);
}
