#include "pipex.h"

void	init_data(t_pipex *p, char **argv)
{
	p->cmd_args = NULL;
	p->cmd = NULL;
	p->env_paths = NULL;
	p->n_cmds = 0;
	p->fd_input = -1;
	p->fd_output = -1;
	p->pipes = NULL;
	p->pid_cmd = -1;
	if (ft_strequal(argv[1], "here_doc"))
		p->mode = HERE_DOC;
	else
		p->mode = PIPE;
	p->limiter = NULL;
}

void	clear_data(t_pipex *p)
{
	if (p->env_paths)
		ft_strarray_clear(&p->env_paths);
	close(p->fd_input);
	close(p->fd_output);
	close_pipes(p);
	if (p->limiter)
		ft_strdel(&p->limiter);
	if (access("inputstream.txt", X_OK) != -1)
	{
		if (unlink("inputstream.txt") == ERROR)
			usage_error(p, "UNLINKING INPUTSTREAM", false);
	}
}

void	open_pipes(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->n_cmds - 1)
	{
		if (pipe(p->pipes + 2 * i) == ERROR)
			program_errors(p, "OPENING PIPES", true);
	}
}

void	close_pipes(t_pipex *p)
{
	int	i;

	if (!p->pipes)
		return ;
	i = -1;
	while (++i < p->n_pipes)
	{
		close(p->pipes[i]);
		p->pipes[i] = -1;
	}
	free(p->pipes);
	p->pipes = NULL;
}

void	dup2_util(t_pipex *p, int read_end, int write_end)
{
	if (dup2(read_end, STDIN_FILENO) == ERROR)
		program_errors(p, "DUP2", true);
	if (dup2(write_end, STDOUT_FILENO) == ERROR)
		program_errors(p, "DUP2", true);
}
