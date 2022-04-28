/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:58:29 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/28 11:53:39 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc(t_pipex *p, int file);
static void	command_paths(t_pipex *p, char **envp);

void	init_pipe_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	if (access(argv[1], F_OK) == ERROR)
	{
		usage_error(p, "NO INPUT FILE", false);
		p->fd_input = STDIN_FILENO;
	}
	else if (access(argv[1], R_OK) == ERROR)
	{
		usage_error(p, "NO PERMISSION", false);
		p->fd_input = STDIN_FILENO;
	}
	else
		p->fd_input = open(argv[1], O_RDONLY);
	if (p->fd_input == ERROR)
		usage_error(p, "OPENING INPUT FILE", false);
	p->fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_output == ERROR)
		usage_error(p, "OPENING OUTPUT FILE", true);
	command_paths(p, envp);
}

void	init_heredoc_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	int	file;

	file = open("inputstream.txt", O_WRONLY | O_CREAT, 0644);
	if (file == ERROR)
		usage_error(p, "OPENING INPUTSTREAM", true);
	p->fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->fd_output == ERROR)
		usage_error(p, "OPENING OUTPUT FILE", true);
	p->limiter = ft_strdup(argv[2]);
	here_doc(p, file);
	close(file);
	p->fd_input = open("inputstream.txt", O_RDONLY);
	if (p->fd_input < 0)
		program_errors(p, "HEREDOC", true);
	command_paths(p, envp);
}

static void	here_doc(t_pipex *p, int file)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(p->limiter, "\n");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			if (ft_strequal(tmp, line))
				break ;
			ft_putstr_fd(line, file);
			ft_strdel(&line);
		}
		else
		{
			ft_strdel(&tmp);
			ft_strdel(&line);
			heredoc_errors(p, true);
		}
	}
	ft_strdel(&tmp);
	ft_strdel(&line);
}

static void	command_paths(t_pipex *p, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	}
	p->env_paths = ft_split(envp[i] + 5, ':');
}
