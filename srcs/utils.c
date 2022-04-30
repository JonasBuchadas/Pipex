/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:59:15 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/29 13:12:51 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_data(t_pipex *p)
{
	if (p->env_paths)
		ft_strarray_clear(&p->env_paths);
	if (p->fd_input != -1)
		close(p->fd_input);
	if (p->fd_output != -1)
		close(p->fd_output);
	close_pipes(p);
	if (p->limiter)
		ft_strdel(&p->limiter);
	if (access(".inputstream.txt", F_OK) != -1)
	{
		if (unlink(".inputstream.txt") == ERROR)
			usage_error(p, "UNLINKING INPUTSTREAM", false, true);
	}
}

void	open_pipes(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->n_cmds - 1)
	{
		if (pipe(p->pipes + 2 * i) == ERROR)
			program_errors(p, "OPENING PIPES", true, true);
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
		program_errors(p, "DUP2", true, true);
	if (dup2(write_end, STDOUT_FILENO) == ERROR)
		program_errors(p, "DUP2", true, true);
}
