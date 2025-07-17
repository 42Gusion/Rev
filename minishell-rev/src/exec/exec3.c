/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:26:15 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 10:31:43 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(const char *cmdname)
{
	if (msh_strcmp("exit", cmdname) == 0
		|| msh_strcmp("cd", cmdname) == 0
		|| msh_strcmp("pwd", cmdname) == 0
		|| msh_strcmp("env", cmdname) == 0
		|| msh_strcmp("echo", cmdname) == 0
		|| msh_strcmp("unset", cmdname) == 0
		|| msh_strcmp("export", cmdname) == 0)
		return (1);
	return (0);
}

static int	connect_pipes(t_exec *ecfg)
{
	if (ecfg->pipe_fd[0] != -1)
		close(ecfg->pipe_fd[0]);
	if (ecfg->read_fd != -1)
	{
		ecfg->status = dup2(ecfg->read_fd, STDIN_FILENO);
		if (ecfg->status == -1)
			return (1);
		close(ecfg->read_fd);
	}
	if (ecfg->pipe_fd[1] != -1)
	{
		ecfg->status = dup2(ecfg->pipe_fd[1], STDOUT_FILENO);
		if (ecfg->status == -1)
			return (1);
		close(ecfg->pipe_fd[1]);
	}
	return (0);
}

int	exec_builtin(t_exec *ecfg)
{
	if (msh_strcmp("exit", ecfg->argv[0]) == 0)
		return (exec_exit(ecfg->argv, ecfg));
	else if (msh_strcmp("cd", ecfg->argv[0]) == 0)
		return (exec_cd(ecfg->argv, &(ecfg->shcfg->envl)));
	else if (msh_strcmp("pwd", ecfg->argv[0]) == 0)
		return (exec_pwd(ecfg->argv, &(ecfg->shcfg->envl)));
	else if (msh_strcmp("env", ecfg->argv[0]) == 0)
		return (exec_env(ecfg->argv, &(ecfg->shcfg->envl)));
	else if (msh_strcmp("echo", ecfg->argv[0]) == 0)
		return (exec_echo(ecfg->argv, &(ecfg->shcfg->envl)));
	else if (msh_strcmp("unset", ecfg->argv[0]) == 0)
		return (exec_unset(ecfg->argv, &(ecfg->shcfg->envl)));
	else if (msh_strcmp("export", ecfg->argv[0]) == 0)
		return (exec_export(ecfg->argv, &(ecfg->shcfg->envl)));
	return (FATALERROR);
}

void	exec_command(t_exec *ecfg)
{
	int	exitno;
	int	fd_outcpy;

	fd_outcpy = dup(STDOUT_FILENO);
	if (fd_outcpy == -1)
		exit(EXIT_FAILURE);
	if (connect_pipes(ecfg))
		exit(EXIT_FAILURE);
	if (prepare_redirections(ecfg->cmdp->redirs, ecfg, fd_outcpy))
	{
		close(fd_outcpy);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(FATALERROR);
	}
	if (is_builtin(ecfg->argv[0]))
		exitno = exec_builtin(ecfg);
	else
		exitno = exec_command_external(ecfg);
	clean_all(ecfg);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(fd_outcpy);
	exit(exitno);
}
