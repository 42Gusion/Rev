/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:09:05 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 04:43:01 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Need to do an overhaul of clean_all its unsafe and can cause problems
void	clean_all(t_exec *ecfg)
{
	if (ecfg->shcfg->envl != NULL)
		env_clr(ecfg->shcfg->envl);
	if (ecfg->shcfg->line != NULL)
		free(ecfg->shcfg->line);
	if (ecfg->shcfg->cmd_list != NULL)
		cmd_clr(ecfg->shcfg->cmd_list);
	if (ecfg->argv != NULL)
		free_strarr(ecfg->argv);
	if (ecfg->envp != NULL)
		free_strarr(ecfg->envp);
	if (ecfg->shcfg->backup_fd[0] != -1)
		close(ecfg->shcfg->backup_fd[0]);
	if (ecfg->shcfg->backup_fd[1] != -1)
		close(ecfg->shcfg->backup_fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (ecfg->pid_list != NULL)
		free(ecfg->pid_list);
}

static int	check_numeric(const char *str)
{
	size_t	pos;

	pos = 0;
	if (str[pos] == '+' || str[pos] == '-')
		pos++;
	while (str[pos] && (str[pos] >= '0' && str[pos] <= '9'))
		pos++;
	return (str[pos] == '\0');
}

int	exec_exit(char **argv, t_exec *ecfg)
{
	int	n;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		msh_putstr("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argv[1] == NULL)
	{
		msh_putstr("exit\n", STDOUT_FILENO);
		clean_all(ecfg);
		exit(ecfg->shcfg->last_exit);
	}
	if (check_numeric(argv[1]))
	{
		msh_putstr("exit\n", STDOUT_FILENO);
		n = msh_atoi(argv[1]);
		clean_all(ecfg);
		exit(n);
	}
	msh_putstr("exit: non-numeric argument\n", STDERR_FILENO);
	clean_all(ecfg);
	exit(255);
}
