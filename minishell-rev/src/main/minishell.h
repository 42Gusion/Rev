/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:53:58 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 22:53:59 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "environment.h"
# include "../pars/parser.h"

# define MSH_PROMPT "msh> "

typedef struct s_shdata
{
	t_env	*envl;
	t_cmd	*cmd_list;
	char	*line;
	int		backup_fd[2];
	int		last_exit;
}	t_msh;

void	signal_cfg(void);

#endif
