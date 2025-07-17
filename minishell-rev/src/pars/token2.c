/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:41 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:42 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	cont_loop(const char c, int state);
static char	*delim_tk(t_tkr *tk, const char c);
static char	*expand_tk(t_tkr *tk, char c);
static void	check_quote(t_tkr *tk, const char quote);
char		*word_next(t_tkr *tk);

static int	cont_loop(const char c, int state)
{
	if (c == '\0')
		return (0);
	else if (state == CONT)
		return (check_char(c) == 0);
	else if (state == SQOT)
		return (c != '\'');
	else if (state == DQOT)
		return (check_char(c) != 4 && c != '\"');
	return (0);
}

static char	*delim_tk(t_tkr *tk, const char c)
{
	if (c == '\0' && tk->s1 == CONT)
		return (tk->s1 = ENDL, msh_strdup("", 0));
	else if (c == '\0' && (tk->s1 == SQOT || tk->s1 == DQOT))
		return (tk->s1 = EQOT, NULL);
	else if (c == '|')
		return (tk->s1 = STOP, tk->p2 += 1, tk_strdup(tk, "|", 1));
	else if (c == '>' && tk->line[tk->p2 + 1] != c)
		return (tk->s1 = STOP, tk->p2 += 1, tk_strdup(tk, ">", 1));
	else if (c == '<' && tk->line[tk->p2 + 1] != c)
		return (tk->s1 = STOP, tk->p2 += 1, tk_strdup(tk, "<", 1));
	else if (c == '>' && tk->line[tk->p2 + 1] == c)
		return (tk->s1 = STOP, tk->p2 += 2, tk_strdup(tk, ">>", 2));
	else if (c == '<' && tk->line[tk->p2 + 1] == c)
		return (tk->s1 = STOP, tk->p2 += 2, tk_strdup(tk, "<<", 2));
	return (tk->s1 = STOP, NULL);
}

static char	*expand_tk(t_tkr *tk, char c)
{
	t_env	*ptr;
	char	*str;

	tk->p2 += 1;
	tk->p1 = tk->p2;
	c = tk->line[tk->p2];
	if (c == '?')
		return (tk->s1 = tk->s2, expand_exit(tk));
	else if (c != '_' && !msh_isalnum(c))
		return (tk->s1 = tk->s2, msh_strdup("$", 1));
	while (c != '\0' && (c == '_' || msh_isalnum(c)))
		c = tk->line[tk->p2++];
	tk->p2 -= 1;
	str = msh_strdup(&tk->line[tk->p1], tk->p2 - tk->p1);
	tk->p1 = tk->p2;
	if (!str)
		return (tk->s1 = ESMT, NULL);
	ptr = env_fnd(tk->env, str);
	free(str);
	tk->s1 = tk->s2;
	if (!ptr)
		return (msh_strdup("", 0));
	ptr = ptr->next;
	return (tk_strdup(tk, ptr->value, msh_strlen(ptr->value, '\0')));
}

static void	check_quote(t_tkr *tk, const char quote)
{
	if (tk->s1 != SQOT && tk->s1 != DQOT)
	{
		if (quote == '\'')
			tk->s1 = SQOT;
		else if (quote == '\"')
			tk->s1 = DQOT;
		tk->p2 += 1;
		tk->p1 = tk->p2;
	}
	else
	{
		if (quote == '\'' && tk->s1 == SQOT)
			tk->s1 = CONT;
		else if (quote == '\"' && tk->s1 == DQOT)
			tk->s1 = CONT;
		else
			return ;
		tk->p2 += 1;
		tk->p1 = tk->p2;
	}
}

char	*word_next(t_tkr *tk)
{
	char	*next;

	tk->p2 = tk->p1;
	if (tk->s1 == EXPN)
		return (expand_tk(tk, tk->line[tk->p2]));
	if (tk->line[tk->p2] == '\0')
		return (delim_tk(tk, tk->line[tk->p2]));
	else if (tk->s1 == CONT && (check_char(tk->line[tk->p2]) == 1
			|| check_char(tk->line[tk->p2]) == 3))
		return (delim_tk(tk, tk->line[tk->p2]));
	if (check_char(tk->line[tk->p2]) == 2)
		check_quote(tk, tk->line[tk->p2]);
	if (check_char(tk->line[tk->p2]) == 4 && tk->s1 != SQOT)
	{
		tk->s2 = tk->s1;
		tk->s1 = EXPN;
	}
	while (cont_loop(tk->line[tk->p2], tk->s1))
		tk->p2++;
	next = msh_strdup(&(tk->line[tk->p1]), tk->p2 - tk->p1);
	return (next);
}
