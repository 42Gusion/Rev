/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 07:39:57 by stariq            #+#    #+#             */
/*   Updated: 2025/05/19 07:39:59 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/param.h>

# include "../util/utils.h"
# include "../main/minishell.h"

// Util for cd:
int	cd_configure_env(t_env **envp, char *new_cwd, t_env *last);
// Function definitions:
int	exec_cd(char **args, t_env **envp);	// unfinished
int	exec_pwd(char **args, t_env **envp);	// done
int	exec_env(char **args, t_env **envp);	// done
int	exec_echo(char **args, t_env **envp);	// done
int	exec_unset(char **args, t_env **envp);	// done
int	exec_export(char **args, t_env **envp);	// testing

#endif
