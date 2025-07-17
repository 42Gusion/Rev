/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:42:37 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:42:39 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_list	t_list;

struct s_list
{
	char	*entry;
	t_list	*next;
};

/*___[strutil1.c]___*/
int		msh_isalnum(const char c);
int		msh_putstr(const char *str, int fd);
int		msh_strcmp(const char *str1, const char *str2);
size_t	msh_strlen(const char *str, const char lim);
char	*msh_strdup(const char *str, size_t size);
/*___[strutil2.c]___*/
char	*msh_strcat(char *dst, const char *src);
char	*msh_strncat(char *dst, const char *src, size_t n);
int		msh_strchr(const char *str, const char c);
int		msh_strncmp(const char *s1, const char *s2, size_t n);
int		msh_atoi(const char *str);
/*___[list.c]___*/
void	list_clr(t_list *hold);
t_list	*list_add(char *entry);
void	list_del(t_list *hold, t_list *prev);

#endif
