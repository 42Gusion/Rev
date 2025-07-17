/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:31:13 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 09:54:34 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_hdoc(t_rdr *head)
{
	t_rdr	*ptr;
	int		count;

	count = 0;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->type == TK_HDC)
			count += 1;
		ptr = ptr->next;
	}
	return (count);
}

static int	prepare_redir(t_rdr *hold, int hdocinfo[2], int out, t_exec *ecfg)
{
	if (hold->type == TK_HDC)
		hold->fd = handle_heredoc(hold, hdocinfo, out, ecfg);
	else if (hold->type == TK_RDI)
		hold->fd = open(hold->info, O_RDONLY);
	else if (hold->type == TK_RDO)
		hold->fd = open(hold->info, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (hold->type == TK_RDA)
		hold->fd = open(hold->info, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (hold->fd == -1)
		return (perror("Fatal: redirection"), 1);
	return (0);
}

static int	connect_last_input(t_rdr *head)
{
	t_rdr	*last;

	last = NULL;
	while (head != NULL)
	{
		if (head->type == TK_HDC || head->type == TK_RDI)
			last = head;
		head = head->next;
	}
	if (last == NULL)
		return (0);
	if (dup2(last->fd, STDIN_FILENO) == -1)
		return (perror("Fatal: redirection"), 1);
	return (0);
}

static int	connect_last_output(t_rdr *head)
{
	t_rdr	*last;

	last = NULL;
	while (head != NULL)
	{
		if (head->type == TK_RDO || head->type == TK_RDA)
			last = head;
		head = head->next;
	}
	if (last == NULL)
		return (0);
	if (dup2(last->fd, STDOUT_FILENO) == -1)
		return (perror("Fatal: redirection"), 1);
	return (0);
}

int	prepare_redirections(t_rdr *redirs, t_exec *ecfg, int out)
{
	t_rdr	*hold;
	int		hdocinfo[2];

	hold = redirs;
	hdocinfo[1] = count_hdoc(hold);
	hdocinfo[0] = 0;
	while (hold != NULL)
	{
		if (prepare_redir(hold, hdocinfo, out, ecfg))
			return (1);
		if (hold->type == TK_HDC)
			hdocinfo[0] += 1;
		hold = hold->next;
	}
	if (connect_last_input(redirs))
		return (1);
	if (connect_last_output(redirs))
		return (1);
	return (0);
}
