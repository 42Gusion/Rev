/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:31:07 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 09:57:01 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	write_subs(char *find, int write_fd, t_env *envl)
{
	t_env	*found;

	found = env_fnd(envl, find);
	if (find)
		free(find);
	if (!found)
		return ;
	else
	{
		found = found->next;
		msh_putstr(found->value, write_fd);
	}
}

static int	heredoc_write(const char *str, t_env *envl,
		int write_fd, size_t pos)
{
	char	*fetched;
	size_t	start;

	while (str[pos] != '\0')
	{
		if (str[pos] == '$')
		{
			pos += 1;
			start = pos;
			while (str[pos]
				&& !((str[pos] > 8 && str[pos] < 14) || str[pos] == 32))
				pos++;
			fetched = msh_strdup(&str[start], pos - start);
			if (!fetched)
				return (1);
			write_subs(fetched, write_fd, envl);
		}
		if (str[pos] == '\0')
			break ;
		write(write_fd, &str[pos], 1);
		pos++;
	}
	msh_putstr("\n", write_fd);
	return (0);
}

static void	heredoc_input(int write_fd, const char *lim, int cnt, t_exec *ecfg)
{
	char	*line;

	while (1)
	{
		line = readline("hdoc> ");
		if (!line)
			break ;
		if (msh_strcmp(lim, line) == 0)
		{
			free(line);
			break ;
		}
		if (cnt - 1 == 0)
		{
			if (heredoc_write(line, ecfg->shcfg->envl, write_fd, 0))
			{
				free(line);
				break ;
			}
		}
		free(line);
	}
	close(write_fd);
	clean_all(ecfg);
	exit(0);
}

static int	close_and_restore(int pipe_read, int out)
{
	close(pipe_read);
	if (out != -1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			return (close(out), 1);
		return (close(out), 0);
	}
	return (0);
}

int	handle_heredoc(t_rdr *hold, int hdci[2], int out, t_exec *ecfg)
{
	int		pipefd[2];
	pid_t	hdoc_id;
	int		stat;

	if (pipe(pipefd) == -1)
		return (perror("Fatal: pipe setup"), 1);
	hdoc_id = fork();
	if (hdoc_id == -1)
		return (close(pipefd[0]), close(pipefd[1]), perror("fork()"), -1);
	if (hdoc_id == 0)
	{
		if (close_and_restore(pipefd[0], out))
			return (close(pipefd[0]), close(pipefd[1]), perror("dup2()"), -1);
		heredoc_input(pipefd[1], hold->info, hdci[1] - hdci[0], ecfg);
	}
	close(pipefd[1]);
	waitpid(hdoc_id, &stat, 0);
	if (WIFEXITED(stat) && WEXITSTATUS(stat) != 0)
		return (close(pipefd[0]), -1);
	return (pipefd[0]);
}
