/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:15:46 by stariq            #+#    #+#             */
/*   Updated: 2024/09/16 19:12:05 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	char_convert(int pid, char *str)
{
	int	i;
	int	b;
	int	n;

	i = 0;
	while (str[i])
	{
		b = 7;
		while (b >= 0)
		{
			if ((str[i] & (1 << b)) > 0)
				n = kill(pid, SIGUSR1);
			else
				n = kill(pid, SIGUSR2);
			b--;
			usleep(150);
		}
		i++;
	}
	if (n == -1)
	{
		write (1, "PID error\n", 11);
		exit(1);
	}
}

int	main(int ac, char *av[])
{
	int	pid;

	if (ac != 3)
	{
		write(1, "ERROR: Wrong Arguments Amount\n", 30);
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (write (1, "Argument Error\n", 16), 1);
	char_convert(pid, av[2]);
	return (0);
}
