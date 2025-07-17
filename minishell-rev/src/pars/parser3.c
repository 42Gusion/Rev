/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:31 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 23:17:14 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	rdr_clr(t_rdr *hold);
t_rdr	*rdr_new(char **info, int type);
void	cmd_clr(t_cmd *hold);
t_cmd	*cmd_new(void);

void	rdr_clr(t_rdr *hold)
{
	t_rdr	*temp;

	while (hold != NULL)
	{
		temp = hold;
		hold = hold->next;
		if (temp->info != NULL)
			free(temp->info);
		if (temp->fd != -1)
			close(temp->fd);
		free(temp);
	}
}

t_rdr	*rdr_new(char **info, int type)
{
	t_rdr	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (free(*info), NULL);
	new->next = NULL;
	new->info = *info;
	new->type = type;
	new->fd = -1;
	return (new);
}

void	cmd_clr(t_cmd *hold)
{
	t_cmd	*temp;

	while (hold != NULL)
	{
		temp = hold;
		hold = hold->next;
		if (temp->args != NULL)
			list_clr(temp->args);
		if (temp->redirs != NULL)
			rdr_clr(temp->redirs);
		free(temp);
	}
}

t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}
