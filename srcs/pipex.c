#include "pipex.h"

static void	init_mode(t_pipex *p, int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;

	init_data(&p, argv);
	init_mode(&p, argc, argv, envp);
	i = -1;
	while (++i < p.n_cmds)
		child_process(&p, i);
	close_pipes(&p);
	waitpid(-1, NULL, 0);
	clear_data(&p);
	exit(EXIT_SUCCESS);
}

static void	init_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	if (argc != 5)
		usage_pipex_error(p, "USAGE", true);
	init_pipe_mode(p, argc, argv, envp);
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->n_cmds = argc - p->mode - 1;
	p->n_pipes = 2 * (p->n_cmds - 1);
	p->pipes = (int *)malloc(sizeof(int) * p->n_pipes);
	if (!p->pipes)
		program_errors(p, "PIPES", true);
	open_pipes(p);
}
