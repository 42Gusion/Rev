/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:13 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:21 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			check_token(t_list *tk);
static char	*rdr_info(t_list **ptr);
t_rdr		*add_rdr(t_list **ptr, t_rdr *head, int *type);
t_list		*add_arg(t_list **ptr, int *type);

int	check_token(t_list *tk)
{
	if (tk == NULL)
		return (TK_END);
	else if (tk->entry[0] == '|' && tk->entry[1] == '\0')
		return (TK_PIP);
	else if (tk->entry[0] == '<' && tk->entry[1] == '<' && tk->entry[2] == '\0')
		return (TK_HDC);
	else if (tk->entry[0] == '>' && tk->entry[1] == '>' && tk->entry[2] == '\0')
		return (TK_RDA);
	else if (tk->entry[0] == '>' && tk->entry[1] == '\0')
		return (TK_RDO);
	else if (tk->entry[0] == '<' && tk->entry[1] == '\0')
		return (TK_RDI);
	return (TK_ARG);
}

static char	*rdr_info(t_list **ptr)
{
	t_list	*temp;
	char	*ret;

	temp = *ptr;
	*ptr = (*ptr)->next;
	list_del(temp, NULL);
	ret = (*ptr)->entry;
	temp = *ptr;
	temp->entry = NULL;
	*ptr = (*ptr)->next;
	list_del(temp, NULL);
	return (ret);
}

t_rdr	*add_rdr(t_list **ptr, t_rdr *head, int *type)
{
	t_rdr	*hold;
	char	*info;

	if ((*ptr)->next == NULL)
		return (rdr_clr(head), *type = -1, NULL);
	info = rdr_info(ptr);
	if (head == NULL)
	{
		head = rdr_new(&info, *type);
		if (!head)
			return (*type = -1, NULL);
		return (*type = check_token(*ptr), head);
	}
	hold = head;
	while (hold->next != NULL)
		hold = hold->next;
	hold->next = rdr_new(&info, *type);
	if (!hold->next)
		return (rdr_clr(head), *type = -1, NULL);
	if (*ptr == NULL)
		return (*type = TK_END, head);
	return (*type = check_token(*ptr), head);
}

t_list	*add_arg(t_list **ptr, int *type)
{
	t_list	*hold;
	t_list	*head;

	if ((*ptr) == NULL)
		return (*type = TK_END, NULL);
	if (*type != TK_ARG)
		return (NULL);
	head = *ptr;
	while (*type == TK_ARG)
	{
		hold = *ptr;
		*ptr = (*ptr)->next;
		if (*ptr == NULL)
			break ;
		*type = check_token(*ptr);
	}
	hold->next = NULL;
	return (head);
}
