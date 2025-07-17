/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:41:42 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:41:43 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# include "../util/utils.h"

typedef struct s_env	t_env;

struct s_env
{
	char	*entry;
	char	*value;
	t_env	*next;
};

t_env	*env_new(char *str);
void	env_clr(t_env *hold);
t_env	*env_fnd(t_env *hold, char *target);
void	env_del(t_env *hold, t_env *prev);
t_env	*env_cfg(char **env);

#endif
