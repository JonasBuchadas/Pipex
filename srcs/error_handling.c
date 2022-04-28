/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:58:47 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/28 09:58:51 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage_error(t_pipex *p, char *usage_name, bool stop)
{
	if (ft_strequal(usage_name, "USAGE"))
	{
		ft_putendl_fd("Not enough arguments given.", 2);
		ft_putstr_fd(usage_name, 2);
		ft_putstr_fd(": ./pipex [filename of input file]", 2);
		ft_putstr_fd(" \"[n Commands (with flags or args)]\"", 2);
		ft_putstr_fd(" [filename of output file]\n", 2);
	}
	else if (ft_strequal(usage_name, "HERE_DOC MODE USAGE"))
	{
		ft_putendl_fd("Incorrect arguments given.", 2);
		ft_putstr_fd(usage_name, 2);
		ft_putstr_fd(": ./pipex here_doc [LIMITER]", 2);
		ft_putstr_fd(" \"[Command 1 (with flags or args)]\"", 2);
		ft_putstr_fd(" \"[Command 2 (with flags or args)]\"", 2);
		ft_putstr_fd(" [filename of output file]\n", 2);
	}
	else
		perror(usage_name);
	if (stop)
	{
		clear_data(p);
		exit(EXIT_FAILURE);
	}
}

void	usage_pipex_error(t_pipex *p, char *usage_name, bool stop)
{
	if (ft_strequal(usage_name, "USAGE"))
	{
		ft_putendl_fd("Incorrect arguments given.", 2);
		ft_putstr_fd(usage_name, 2);
		ft_putstr_fd(": ./pipex [filename of input file]", 2);
		ft_putstr_fd(" \"[Command 1 (with flags or args)]\"", 2);
		ft_putstr_fd(" \"[Command 2 (with flags or args)]\"", 2);
		ft_putstr_fd(" [filename of output file]\n", 2);
	}
	else
		perror(usage_name);
	if (stop)
	{
		clear_data(p);
		exit(EXIT_FAILURE);
	}
}

void	program_errors(t_pipex *p, char *errname, bool stop)
{
	perror(errname);
	if (stop)
	{
		clear_data(p);
		exit(EXIT_FAILURE);
	}
}

void	command_errors(t_pipex *p, char *errname, bool stop)
{
	char	*line;

	line = ft_strjoin("Command not found: ", errname);
	ft_putendl_fd(line, 2);
	ft_strdel(&line);
	if (stop)
	{
		clear_data(p);
		exit(EXIT_FAILURE);
	}
}

void	heredoc_errors(t_pipex *p, bool stop)
{
	ft_putendl_fd("LIMITER not found in here_doc", 2);
	if (stop)
	{
		clear_data(p);
		exit(EXIT_FAILURE);
	}
}
