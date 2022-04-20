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
	char	***commands;
	int		n_cmds;
	int		fd_input;
	int		fd_out;
	int		pipe[2];
	pid_t	pid_cmd;
	int		wstatus;
	int		mode;
	char	*limiter;
}			t_pipex;

void	init_data(t_pipex *p, char **argv);
void	check_pipe_mode(t_pipex *p, int argc, char **argv, char **envp);
void	check_heredoc_mode(t_pipex *p, int argc, char **argv, char **envp);
void	clear_data(t_pipex *p);
void	usage_error(t_pipex *p, char *usage_name, bool stop);
void	program_errors(t_pipex *p, char *errname, bool stop);
void	clear_data(t_pipex *p);
void	open_pipe(t_pipex *p, int fd[2]);
void	close_pipe(int *pipe);
void	dup2_util(t_pipex *p, int fd1, int fd2);
void    exec_cmd(t_pipex *p, char *full_cmd);

#endif