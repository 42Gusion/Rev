/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:27:52 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:27:53 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "../util/utils.h"
# include "../main/environment.h"

# define CONT 1
# define SQOT 2
# define DQOT 3
# define EXPN 4
# define SPTK 5
# define STOP 6
# define EQOT 7
# define ESMT 8
# define ENDL 0

typedef struct s_tokenizer	t_tkr;

struct s_tokenizer
{
	t_env	*env;
	t_list	*tokn_list;
	t_list	*word_list;
	char	*line;
	size_t	p1;
	size_t	p2;
	int		s1;
	int		s2;
	int		last_exit_stat;
};

// token3.c
int		line_is_empty(const char *l);
int		check_char(const char c);
char	*expand_exit(t_tkr *tk);
char	*tk_strdup(t_tkr *tk, const char *str, size_t len);
// token2.c
char	*word_next(t_tkr *tk);
// token1.c
t_list	*get_token_list(char *line, t_env *envlist, int extl);

#endif
