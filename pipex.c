#include "pipex.h"

static void check_input(t_pipex *p, int argc, char **argv, char **envp);
//static void	here_doc(t_pipex *p);
//static void	write2pipe(t_pipex *p, int fd[2]);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	init_data(&p, argv);
	check_input(&p, argc, argv, envp);
//	get_commands(&p);
//	if (p.mode == PIPE)
//		pipe_mode(&p);
//	else if (p.mode == HERE_DOC)
//		here_doc_mode(&p);
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
/*
static void	here_doc(t_pipex *p)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		program_errors(p, "Pipe", true);
	pid = fork();
	if (pid == -1)
		program_errors(p, "Fork", true);
	if (pid == 0)
		write2pipe(p, fd);
	else
	{
		dup2_util(p, fd[READ_END], STDIN_FILENO);
		close_pipe(fd);
		waitpid(pid, NULL, 0);
	}
}

static void	write2pipe(t_pipex *p, int fd[2])
{
	size_t	limiter_length;
	char	*line;

	limiter_length = ft_strlen(p->limiter);
	while (1)
	{
		ft_putstr_fd("pipex here_doc> ", 1);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
		{
			close_pipe(fd);
			program_errors(p, "HereDoc", true);
		}
		if (line[limiter_length] == '\n' && p->limiter && \
			!ft_strncmp(line, p->limiter, limiter_length))
		{
			close_pipe(fd);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[1]);
		ft_strdel(&line);
	}
}
*/