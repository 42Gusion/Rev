/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:15:15 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 09:58:48 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	single_execute_handle_fds(int fd_copy[2], int state)
{
	if (state == 0)
	{
		fd_copy[0] = dup(STDIN_FILENO);
		if (fd_copy[0] == -1)
			return (1);
		fd_copy[1] = dup(STDOUT_FILENO);
		if (fd_copy[1] == -1)
			return (close(fd_copy[0]), 1);
	}
	else if (state == 1)
	{
		state = dup2(fd_copy[0], STDIN_FILENO);
		if (state == -1)
			return (1);
		state = dup2(fd_copy[1], STDOUT_FILENO);
		if (state == -1)
			return (1);
		close(fd_copy[0]);
		close(fd_copy[1]);
		fd_copy[0] = -1;
		fd_copy[1] = -1;
	}
	return (0);
}

static int	execute_single(t_exec *ecfg)
{
	if (ecfg->cmdp->redirs != NULL)
	{
		if (single_execute_handle_fds(ecfg->shcfg->backup_fd, 0))
			return (EXIT_FAILURE);
	}
	if (prepare_redirections(ecfg->cmdp->redirs, ecfg, -1))
		return (close(ecfg->shcfg->backup_fd[0]),
			close(ecfg->shcfg->backup_fd[1]), EXIT_FAILURE);
	ecfg->argv = create_argv(ecfg->cmdp->args);
	if (!ecfg->argv)
		return (close(ecfg->shcfg->backup_fd[0]),
			close(ecfg->shcfg->backup_fd[1]), EXIT_FAILURE);
	ecfg->status = exec_builtin(ecfg);
	free_strarr(ecfg->argv);
	if (ecfg->cmdp->redirs != NULL)
	{
		if (single_execute_handle_fds(ecfg->shcfg->backup_fd, 1))
			return (perror("Fatal: fd restoration"), EXIT_FAILURE);
	}
	return (ecfg->status);
}

static int	prepare_execution(t_exec *ecfg)
{
	t_cmd	*hold;

	hold = ecfg->cmdp;
	while (hold != NULL)
	{
		ecfg->cmdcnt += 1;
		hold = hold->next;
	}
	ecfg->pid_list = malloc(sizeof(pid_t) * ecfg->cmdcnt);
	if (!ecfg->pid_list)
		return (1);
	return (0);
}

int	msh_execute(t_msh *sh)
{
	t_exec	ecfg;

	ecfg.shcfg = sh;
	ecfg.envp = NULL;
	ecfg.argv = NULL;
	ecfg.pid_list = NULL;
	ecfg.cmdp = sh->cmd_list;
	ecfg.read_fd = -1;
	if (ecfg.cmdp->next == NULL && is_builtin(ecfg.cmdp->args->entry))
		return (execute_single(&ecfg));
	ecfg.cmdcnt = 0;
	ecfg.cmdpos = 0;
	ecfg.status = 0;
	if (prepare_execution(&ecfg))
		return (EXIT_FAILURE);
	ecfg.envp = create_envp(ecfg.shcfg->envl);
	if (!ecfg.envp)
		return (free(ecfg.pid_list), EXIT_FAILURE);
	sh->last_exit = execute_commands(&ecfg);
	cmd_clr(sh->cmd_list);
	sh->cmd_list = NULL;
	return (sh->last_exit);
}
