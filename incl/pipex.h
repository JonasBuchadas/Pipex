/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:04:11 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/28 10:04:12 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define WRITE_END 1
# define READ_END 0
# define CHILD_PROCESS 0
# define ERROR -1
# define PIPE 2
# define HERE_DOC 3

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**env_paths;
	char	**cmd_args;
	char	*cmd;
	int		n_cmds;
	int		n_pipes;
	int		fd_input;
	int		fd_output;
	int		*pipes;
	pid_t	pid_cmd;
	int		mode;
	char	*limiter;
}			t_pipex;

void	init_data(t_pipex *p, char **argv);
void	init_pipe_mode(t_pipex *p, int argc, char **argv, char **envp);
void	init_heredoc_mode(t_pipex *p, int argc, char **argv, char **envp);
void	clear_data(t_pipex *p);
void	usage_error(t_pipex *p, char *usage_name, bool stop);
void	usage_pipex_error(t_pipex *p, char *usage_name, bool stop);
void	program_errors(t_pipex *p, char *errname, bool stop);
void	clear_data(t_pipex *p);
void	open_pipes(t_pipex *p);
void	close_pipes(t_pipex *p);
void	dup2_util(t_pipex *p, int fd1, int fd2);
void	child_process(t_pipex *p, int cmd);
void	command_errors(t_pipex *p, char *errname, bool stop);
void	heredoc_errors(t_pipex *p, bool stop);

#endif
