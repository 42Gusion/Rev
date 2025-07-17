/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:42:48 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:42:48 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	list_clr(t_list *hold);
t_list	*list_add(char *entry);
void	list_del(t_list *hold, t_list *prev);

void	list_clr(t_list *hold)
{
	t_list	*prev;

	while (hold != NULL)
	{
		prev = hold;
		hold = hold->next;
		if (prev->entry)
			free(prev->entry);
		free(prev);
	}
}

t_list	*list_add(char *entry)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!entry)
		return (new->entry = NULL, new);
	new->entry = entry;
	return (new);
}

void	list_del(t_list *hold, t_list *prev)
{
	if (prev != NULL)
		prev->next = hold->next;
	if (hold->entry != NULL)
		free(hold->entry);
	free(hold);
}
