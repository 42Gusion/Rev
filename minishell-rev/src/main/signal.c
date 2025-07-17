/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:41:24 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:41:25 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_cfg(void)
{
	struct sigaction	sa_sigquit;
	struct sigaction	sa_sigint;

	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigint.sa_handler = &sigint_handler;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
	sigaction(SIGINT, &sa_sigint, NULL);
}
