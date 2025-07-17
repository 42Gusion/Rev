/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutil1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:50:48 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/18 20:28:09 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	msh_strlen(const char *str, const char lim);
int		msh_putstr(const char *str, int fd);
int		msh_strcmp(const char *str1, const char *str2);
char	*msh_strdup(const char *str, size_t size);
int		msh_isalnum(const char c);

size_t	msh_strlen(const char *str, const char lim)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0' && str[len] != lim)
		len++;
	return (len);
}

int	msh_putstr(const char *str, int fd)
{
	write(fd, str, msh_strlen(str, '\0'));
	return (0);
}

int	msh_strcmp(const char *str1, const char *str2)
{
	size_t	pos1;
	size_t	pos2;

	pos1 = 0;
	pos2 = 0;
	while (str1[pos1] && str2[pos2] && str1[pos1] == str2[pos2])
	{
		pos1++;
		pos2++;
	}
	return (str1[pos1] - str2[pos2]);
}

char	*msh_strdup(const char *str, size_t size)
{
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	while (size-- != 0)
		new[size] = str[size];
	return (new);
}

int	msh_isalnum(const char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
