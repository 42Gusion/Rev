/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:06 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:07 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"

static int		parse_one(t_list **ptr, t_cmd *hold);
static t_cmd	*check_tokens(t_list *tokens, t_cmd *head);
t_cmd			*get_cmd_list(char *line, t_env *envl, int last_exit);

static int	check_pipe(t_list **ptr)
{
	t_list	*temp;

	temp = *ptr;
	*ptr = (*ptr)->next;
	list_del(temp, NULL);
	if (*ptr == NULL)
		return (-1);
	return (check_token(*ptr));
}

static int	parse_one(t_list **ptr, t_cmd *hold)
{
	t_cmd	*cmdn;
	int		type;

	cmdn = cmd_new();
	if (!cmdn)
		return (-1);
	type = check_token(*ptr);
	if (type == TK_PIP)
		type = check_pipe(ptr);
	while (type > TK_PIP && *ptr != NULL)
		cmdn->redirs = add_rdr(ptr, cmdn->redirs, &type);
	if (type == -1)
		return (-1);
	cmdn->args = add_arg(ptr, &type);
	while (type > TK_PIP && *ptr != NULL)
		cmdn->redirs = add_rdr(ptr, cmdn->redirs, &type);
	if (type == -1)
		return (-1);
	hold->next = cmdn;
	if (type == TK_PIP)
		return (1);
	return (0);
}

static t_cmd	*check_tokens(t_list *tokens, t_cmd *head)
{
	t_cmd	*hold;
	t_list	*ptr;
	int		cont;

	cont = 1;
	hold = head;
	ptr = tokens->next;
	while (cont == 1)
	{
		cont = parse_one(&ptr, hold);
		hold = hold->next;
	}
	if (cont == -1)
	{
		msh_putstr("Error: Parser\n", STDERR_FILENO);
		cmd_clr(head);
		return (NULL);
	}
	hold = head->next;
	head->next = NULL;
	cmd_clr(head);
	return (hold);
}

t_cmd	*get_cmd_list(char *line, t_env *envl, int last_exit)
{
	t_cmd	*head;
	t_list	*tokens;

	tokens = get_token_list(line, envl, last_exit);
	if (!tokens)
		return (NULL);
	head = cmd_new();
	if (!head)
		return (NULL);
	head = check_tokens(tokens, head);
	return (head);
}
