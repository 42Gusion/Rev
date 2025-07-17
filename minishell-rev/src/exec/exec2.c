/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:05:44 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 04:48:05 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	prepare_pipes(t_exec *ecfg)
{
	if (ecfg->cmdpos == ecfg->cmdcnt - 1)
	{
		ecfg->pipe_fd[0] = -1;
		ecfg->pipe_fd[1] = -1;
		return (0);
	}
	ecfg->status = pipe(ecfg->pipe_fd);
	if (ecfg->status == -1)
	{
		ecfg->pipe_fd[0] = -1;
		ecfg->pipe_fd[1] = -1;
		return (perror("Fatal: failed to create pipe"), 1);
	}
	return (0);
}

static void	clean_pipes(t_exec *ecfg)
{
	if (ecfg->read_fd != -1)
		close(ecfg->read_fd);
	if (ecfg->pipe_fd[0] != -1)
		close(ecfg->pipe_fd[0]);
	if (ecfg->pipe_fd[1] != -1)
		close(ecfg->pipe_fd[1]);
}

static int	execute_commands_one(t_exec *ecfg)
{
	if (prepare_pipes(ecfg))
		return (clean_pipes(ecfg), 1);
	ecfg->argv = create_argv(ecfg->cmdp->args);
	if (!ecfg->argv)
		return (clean_pipes(ecfg), 1);
	ecfg->pid_list[ecfg->cmdpos] = fork();
	if (ecfg->pid_list[ecfg->cmdpos] == -1)
		return (clean_pipes(ecfg), free_strarr(ecfg->argv), 1);
	else if (ecfg->pid_list[ecfg->cmdpos] == 0)
		exec_command(ecfg);
	if (ecfg->read_fd != -1)
		close(ecfg->read_fd);
	ecfg->read_fd = ecfg->pipe_fd[0];
	if (ecfg->pipe_fd[1] != -1)
		close(ecfg->pipe_fd[1]);
	free_strarr(ecfg->argv);
	ecfg->argv = NULL;
	return (0);
}

static int	wait_for_commands(t_exec *ecfg)
{
	int		last;
	int		wstat;
	int		wpos;
	pid_t	wpid;

	wpos = 0;
	last = 0;
	if (ecfg->cmdpos == ecfg->cmdcnt)
		ecfg->cmdpos -= 1;
	while (wpos <= ecfg->cmdpos)
	{
		wpid = waitpid(ecfg->pid_list[wpos], &wstat, 0);
		if (wpid == ecfg->pid_list[ecfg->cmdpos])
		{
			if (WIFEXITED(wstat))
				last = WEXITSTATUS(wstat);
			else if (WIFSIGNALED(wstat))
				last = 128 + WTERMSIG(wstat);
			break ;
		}
		wpos += 1;
	}
	return (last);
}

int	execute_commands(t_exec *ecfg)
{
	int	last_exit_status;

	while (ecfg->cmdpos < ecfg->cmdcnt && ecfg->status != -1)
	{
		if (execute_commands_one(ecfg))
			break ;
		ecfg->cmdp = ecfg->cmdp->next;
		ecfg->cmdpos += 1;
	}
	if (ecfg->cmdpos != ecfg->cmdcnt)
		perror("Something went wrong");
	last_exit_status = wait_for_commands(ecfg);
	free_strarr(ecfg->envp);
	free(ecfg->pid_list);
	if (ecfg->read_fd != -1)
		close(ecfg->read_fd);
	return (last_exit_status);
}
