/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:14:07 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 06:21:26 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../pars/parser.h"
#include "../exec/exec.h"

static int	shell_cfg(t_msh *sh, char **env)
{
	signal_cfg();
	sh->envl = env_cfg(env);
	if (!sh->envl)
		return (1);
	sh->cmd_list = NULL;
	sh->line = NULL;
	sh->last_exit = 0;
	sh->backup_fd[0] = -1;
	sh->backup_fd[1] = -1;
	return (0);
}

static void	line_helper(t_msh *sh)
{
	add_history(sh->line);
	free(sh->line);
}

static void	minishell_start(t_msh *sh)
{
	while (1)
	{
		sh->line = readline(MSH_PROMPT);
		if (!sh->line)
			break ;
		sh->cmd_list = get_cmd_list(sh->line, sh->envl, sh->last_exit);
		if (!sh->cmd_list)
		{
			line_helper(sh);
			continue ;
		}
		sh->last_exit = msh_execute(sh);
		line_helper(sh);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msh	data;

	((void)argc, (void)argv);
	if (shell_cfg(&data, env))
		return (EXIT_FAILURE);
	minishell_start(&data);
	return (EXIT_SUCCESS);
}
