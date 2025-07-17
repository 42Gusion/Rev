/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:45 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:46 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int		check_char(const char c);
char	*expand_exit(t_tkr *tk);
char	*tk_strdup(t_tkr *tk, const char *str, size_t len);

int	check_char(const char c)
{
	static const int	table[256] = {
	[' '] = 1,
	['\t'] = 1,
	['\n'] = 1,
	['\''] = 2,
	['\"'] = 2,
	['|'] = 3,
	['<'] = 3,
	['>'] = 3,
	['$'] = 4
	};

	return (table[(int)c]);
}

char	*expand_exit(t_tkr *tk)
{
	char	*str;
	int		len;
	int		n;

	len = 1;
	tk->p2 += 1;
	n = tk->last_exit_stat;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (tk->s1 = ESMT, NULL);
	n = tk->last_exit_stat;
	str[len] = '\0';
	while (len--)
	{
		str[len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*tk_strdup(t_tkr *tk, const char *str, size_t len)
{
	char	*ret;

	ret = msh_strdup(str, len);
	if (!ret)
		return (tk->s1 = ESMT, NULL);
	return (ret);
}

int	line_is_empty(const char *l)
{
	size_t	n;

	n = 0;
	while (l[n] && (l[n] == 32 || (l[n] > 8 && l[n] < 14)))
		n++;
	return (l[n] == '\0');
}
