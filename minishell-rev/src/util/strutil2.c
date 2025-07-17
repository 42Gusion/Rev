/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutil2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:28:03 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:28:04 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*msh_strcat(char *dst, const char *src)
{
	char	*start;

	start = dst;
	dst += msh_strlen(dst, '\0');
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (start);
}

char	*msh_strncat(char *dst, const char *src, size_t n)
{
	char	*start;

	start = dst;
	dst += msh_strlen(dst, '\0');
	while (n && *src)
	{
		*dst++ = *src++;
		n--;
	}
	*dst = '\0';
	return (start);
}

int	msh_strchr(const char *str, const char c)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != c)
		pos++;
	return (str[pos] == c);
}

int	msh_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	while (s1[pos] != '\0' && s2[pos] != '\0'
		&& s1[pos] == s2[pos] && pos < n - 1)
		pos++;
	return (s1[pos] - s2[pos]);
}

int	msh_atoi(const char *str)
{
	long long	count;
	int			sign;

	sign = 1;
	count = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (count > INT_MAX)
			break ;
		count = (count * 10) + (*str++ - '0');
	}
	if (count > INT_MAX && sign == 1)
		return (INT_MAX);
	else if (count > INT_MAX && sign == -1)
		return (INT_MIN);
	return ((int)count * sign);
}
