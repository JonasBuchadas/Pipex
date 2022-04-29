/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:58:47 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/29 15:22:33 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage_error(t_pipex *p, char *usage_name, bool clear, bool stop)
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
	if (clear)
		clear_data(p);
	if (stop)
		exit(EXIT_FAILURE);
}

void	usage_pipex_error(t_pipex *p, char *usage_name, bool clear, bool stop)
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
	if (clear)
		clear_data(p);
	if (stop)
		exit(EXIT_FAILURE);
}

void	program_errors(t_pipex *p, char *errname, bool clear, bool stop)
{
	perror(errname);
	if (clear)
		clear_data(p);
	if (stop)
		exit(EXIT_FAILURE);
}

void	command_errors(char *errname, bool stop)
{
	char	*line;

	line = ft_strjoin("pipex: command not found: ", errname);
	ft_putendl_fd(line, 2);
	ft_strdel(&line);
	if (stop)
		exit(EXIT_FAILURE);
}

void	file_error(char *error, char *filename, bool stop)
{
	char	*line;

	if (ft_strequal(error, "NO FILE"))
		line = ft_strjoin("pipex: no such file or directory: ", filename);
	else
		line = ft_strjoin("pipex: permission denied: ", filename);
	ft_putendl_fd(line, 2);
	ft_strdel(&line);
	if (stop)
		exit(EXIT_FAILURE);
}
