#include "pipex.h"

static void check_input(t_pipex *p, int argc, char **argv, char **envp);
static void	pipe_mode(t_pipex *p);
static void	heredoc_mode(t_pipex *p);
static void child_cmd(t_pipex *p, int cmd_index);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	init_data(&p, argv);
	check_input(&p, argc, argv, envp);
	if (p.mode == PIPE)
		pipe_mode(&p);
	else if (p.mode == HERE_DOC)
		heredoc_mode(&p);
	clear_data(&p);
	exit(EXIT_SUCCESS);
}

static void	check_input(t_pipex *p, int argc, char **argv, char **envp)
{
	if (p->mode == HERE_DOC)
	{
		if (argc != 6)
			usage_error(p, "HERE_DOC MODE USAGE", true);
		check_heredoc_mode(p, argc, argv, envp);
	}
	else
	{
		if (argc < 5)
			usage_error(p, "USAGE", true);
		check_pipe_mode(p, argc, argv, envp);
	}
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
}

static void	pipe_mode(t_pipex *p)
{
	int	cmd_index;

	cmd_index = PIPE;
	while (cmd_index < p->argc - 2)
		child_cmd(p, cmd_index++);
	dup2_util(p, p->fd_out, STDOUT_FILENO);
	exec_cmd(p, p->argv[p->argc - 2]);		
}

static void	heredoc_mode(t_pipex *p)
{
	int	cmd_index;

	cmd_index = HERE_DOC;
	while (cmd_index < p->argc - 2)
		child_cmd(p, cmd_index++);
	dup2_util(p, p->fd_out, STDOUT_FILENO);
	exec_cmd(p, p->argv[p->argc - 2]);		
}

static void child_cmd(t_pipex *p, int cmd_index)
{
	pid_t	pid;
	int		fd[2];

	open_pipe(p, fd);
	pid = fork();
	if (pid == -1)
		program_errors(p, "FORK", true);
	if (pid == CHILD_PROCESS)
	{
		if (p->fd_input == -1)
		{
			close_pipe(fd);
			program_errors(p, "STDIN", true);
		}
		dup2_util(p, fd[1], STDOUT_FILENO);
		close_pipe(fd);
		exec_cmd(p, p->argv[cmd_index]);
	}
	dup2_util(p, fd[0], STDIN_FILENO);
	close_pipe(fd);
	waitpid(-1, NULL, WNOHANG);
}