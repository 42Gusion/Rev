/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:18:53 by ialkhali          #+#    #+#             */
/*   Updated: 2025/04/13 22:00:43 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <string.h>

# include "../util/utils.h"
# include "../main/environment.h"

# define TK_NON 0
# define TK_ARG 2
# define TK_PIP 3
# define TK_RDI 4
# define TK_RDO 5
# define TK_RDA 6
# define TK_HDC 7
# define TK_END 9

# define AST_CMD 1
# define AST_CON 2

typedef struct s_rdr	t_rdr;
typedef struct s_cmd	t_cmd;

struct s_rdr
{
	t_rdr	*next;
	char	*info;
	int		fd;
	int		type;
};

struct s_cmd
{
	t_list	*args;
	t_cmd	*next;
	t_rdr	*redirs;
};

// parser3.c 
t_rdr	*rdr_new(char **info, int type);
t_cmd	*cmd_new(void);
void	rdr_clr(t_rdr *hold);
void	cmd_clr(t_cmd *hold);
// parser2.c
int		check_token(t_list *tk);
t_rdr	*add_rdr(t_list **ptr, t_rdr *head, int *type);
t_list	*add_arg(t_list **ptr, int *type);
// parser1.c
t_cmd	*get_cmd_list(char *line, t_env *envl, int last_exit);

#endif
