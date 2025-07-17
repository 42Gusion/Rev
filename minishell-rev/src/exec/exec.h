/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialkhali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:28:36 by ialkhali          #+#    #+#             */
/*   Updated: 2025/05/19 09:48:04 by ialkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>

# include <sys/wait.h>
# include <fcntl.h>

# include "../util/utils.h"
# include "../bltn/builtin.h"
# include "../main/minishell.h"

# define CMDNOTFND 127
# define FATALERROR 14

typedef struct s_exec
{
	t_msh	*shcfg;
	t_cmd	*cmdp;
	pid_t	*pid_list;
	char	**argv;
	char	**envp;
	int		pipe_fd[2];
	int		read_fd;
	int		status;
	int		cmdpos;
	int		cmdcnt;
}	t_exec;

// exit.c
int		exec_exit(char **argv, t_exec *ecfg);
void	clean_all(t_exec *ecfg);
// exec7.c
void	free_strarr(char **arr);
char	**create_envp(t_env *envl);
char	**create_argv(t_list *args);
// exec6.c
int		handle_heredoc(t_rdr *hold, int hdci[2], int out, t_exec *ecfg);
// exec5.c
int		prepare_redirections(t_rdr *redirs, t_exec *ecfg, int out);
// exec4.c
int		exec_command_external(t_exec *ecfg);
// exec3.c
int		is_builtin(const char *cmdname);
int		exec_builtin(t_exec *ecfg);
void	exec_command(t_exec *ecfg);
// exec2.c
int		execute_commands(t_exec *ecfg);
// exec1.c
int		msh_execute(t_msh *sh);

#endif
