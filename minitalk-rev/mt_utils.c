/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:15:27 by stariq            #+#    #+#             */
/*   Updated: 2024/09/16 19:15:45 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	over_flow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	result_check(long long result, char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		if (result > (2147483647))
		{
			over_flow(sign);
			return (over_flow(sign));
		}
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (result_check(result, (char *)str + i));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd ('-', fd);
		ft_putchar_fd ('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd ('-', fd);
		n = n * -1;
	}
	if (n < 10)
	{
		n = n + 48;
		write (fd, &n, 1);
		return ;
	}
	else
		ft_putnbr_fd (n / 10, fd);
	ft_putnbr_fd (n % 10, fd);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
