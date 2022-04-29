/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:59:05 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/29 14:10:46 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_pipex *p, char **argv);
static void	init_mode(t_pipex *p, int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;

	init_data(&p, argv);
	init_mode(&p, argc, argv, envp);
	if (p.fd_input == NO_INPUT_FILE)
		i = 0;
	else
		i = -1;
	while (++i < p.n_cmds)
		child_process(&p, i);
	close_pipes(&p);
	waitpid(-1, NULL, 0);
	clear_data(&p);
	exit(EXIT_SUCCESS);
}

static void	init_data(t_pipex *p, char **argv)
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

static void	init_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	if (p->mode == HERE_DOC)
	{
		if (argc != 6)
			usage_error(p, "HERE_DOC MODE USAGE", true, true);
		init_heredoc_mode(p, argc, argv, envp);
	}
	else
	{
		if (argc < 5)
			usage_error(p, "USAGE", true, true);
		init_pipe_mode(p, argc, argv, envp);
	}
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->n_cmds = argc - p->mode - 1;
	p->n_pipes = 2 * (p->n_cmds - 1);
	p->pipes = (int *)malloc(sizeof(int) * p->n_pipes);
	if (!p->pipes)
		program_errors(p, "PIPES", true, true);
	open_pipes(p);
}
