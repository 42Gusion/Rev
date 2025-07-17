/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:36 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:37 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static char	*word_join(t_list *head);
static int	word_loop(t_tkr *tk, t_list *last);
static int	token_next(t_tkr *tk, t_list *last);
t_list		*get_token_list(char *line, t_env *envlist, int extl);

static char	*word_join(t_list *head)
{
	t_list	*hold;
	char	*str;
	size_t	size;

	size = 0;
	hold = head->next;
	while (hold != NULL)
	{
		size += msh_strlen(hold->entry, '\0');
		hold = hold->next;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (list_clr(head), NULL);
	hold = head->next;
	str[0] = '\0';
	while (hold != NULL)
	{
		str = msh_strcat(str, hold->entry);
		hold = hold->next;
	}
	return (list_clr(head), str);
}

static int	word_loop(t_tkr *tk, t_list *last)
{
	t_list	*wptr;
	char	*word;

	wptr = tk->word_list;
	while (tk->s1 < STOP && tk->s1 != ENDL)
	{
		word = word_next(tk);
		if (!word && tk->s1 >= EQOT)
			return (list_clr(tk->word_list), tk->s1);
		tk->p1 = tk->p2;
		if (word == NULL)
			continue ;
		wptr->next = list_add(word);
		if (!wptr->next)
			return (list_clr(tk->word_list), ESMT);
		wptr = wptr->next;
		if (check_char(tk->line[tk->p2]) == 3 && tk->s1 != SQOT)
			break ;
	}
	word = word_join(tk->word_list);
	last->next = list_add(word);
	if (!word || !last->next)
		return (ESMT);
	return (CONT);
}

static int	token_next(t_tkr *tk, t_list *last)
{
	int	state;

	tk->word_list = list_add(NULL);
	if (!tk->word_list)
		return (ESMT);
	while (check_char(tk->line[tk->p1]) == 1)
		tk->p1++;
	if (tk->line[tk->p1] == '\0')
		return (ENDL);
	state = word_loop(tk, last);
	if (state == EQOT)
		msh_putstr("Error: Unclosed quotes\n", STDERR_FILENO);
	else if (state == ESMT)
		msh_putstr("Error: Memory allocate\n", STDERR_FILENO);
	return (state);
}

t_list	*get_token_list(char *line, t_env *envlist, int extl)
{
	t_tkr	data;
	t_list	*ptr;

	if (line_is_empty(line))
		return (NULL);
	data.env = envlist;
	data.tokn_list = list_add(NULL);
	if (!data.tokn_list)
		return (NULL);
	data.word_list = NULL;
	data.line = line;
	data.p1 = 0;
	data.p2 = 0;
	data.s1 = CONT;
	data.s2 = 0;
	data.last_exit_stat = extl;
	ptr = data.tokn_list;
	while (data.line[data.p1] != '\0' && data.s1 < STOP)
	{
		data.s1 = token_next(&data, ptr);
		ptr = ptr->next;
	}
	if (data.s1 >= EQOT)
		return (list_clr(data.tokn_list), NULL);
	return (data.tokn_list);
}
