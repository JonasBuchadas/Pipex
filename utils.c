#include "pipex.h"

void	init_data(t_pipex *p, char **argv)
{
	p->commands = NULL;
	p->env_paths = NULL;
	p->n_cmds = 0;
	p->fd_input = -1;
	p->fd_out = -1;
	p->pipe[0] = -1;
	p->pipe[1] = -1;
	p->pid_cmd = -1;
	if (ft_strequal(argv[1], "here_doc"))
		p->mode = HERE_DOC;
	else
		p->mode = PIPE;
	p->limiter = NULL;
}

void	clear_data(t_pipex *p)
{
	int	i;

	if (p->commands)
	{
		i = -1;
		while (p->commands[++i])
			ft_strarray_clear(&p->commands[i]);
		free(p->commands);
		p->commands = NULL;
	}
	if (p->env_paths)
		ft_strarray_clear(&p->env_paths);
	close(p->fd_input);
	close(p->fd_out);
	close_pipe(p->pipe);
	if (p->limiter)
		ft_strdel(&p->limiter);
	if (access("inputstream.txt", X_OK) != -1)
	{
		if (unlink("inputstream.txt") == ERROR)
			usage_error(p, "UNLINKING INPUTSTREAM", false);
	}
}

void	open_pipe(t_pipex *p, int fd[2])
{
	if (pipe(fd) == ERROR)
		program_errors(p, "OPENING PIPE", true);
}

void	close_pipe(int *pipe)
{
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	pipe[READ_END] = -1;
	pipe[WRITE_END] = -1;
}

void	dup2_util(t_pipex *p, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == ERROR)
		program_errors(p, "DUP2", true);
}