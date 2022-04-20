#include "pipex.h"

static void here_doc(t_pipex *p, int file);
static void	command_paths(t_pipex *p, char **envp);

void	check_pipe_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	if (access(argv[1], F_OK) == ERROR)
		usage_error(p, "NO INPUT FILE", true);
	if (access(argv[1], R_OK) == ERROR)
		usage_error(p, "NO PERMISSION", true);
	p->fd_input = open(argv[1], O_RDONLY);
	if (p->fd_input == ERROR)
		usage_error(p, "OPENING INPUT FILE", true);
	p->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (p->fd_out == ERROR)
		usage_error(p, "OPENING OUTPUT FILE", true);
	command_paths(p, envp);
}

void	check_heredoc_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	int file;

	file = open("inputstream.txt", O_WRONLY | O_CREAT, 0777);
	if (file == ERROR)
		usage_error(p, "OPENING INPUTSTREAM", true);
	p->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (p->fd_out == ERROR)
		usage_error(p, "OPENING OUTPUT FILE", true);
	p->limiter = ft_strdup(argv[2]);
	here_doc(p, file);
	close(file);
	p->fd_input = open("inputstream.txt", O_RDONLY);
	if (p->fd_input < 0)
		program_errors(p, "HEREDOC", true);
	command_paths(p, envp);
}

static void here_doc(t_pipex *p, int file)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(p->limiter, "\n");
	while (1)
	{
		ft_putendl_fd("pipe heredoc> ", 1);
		line = ft_get_next_line(STDIN_FILENO);
		if (line)
		{
			if (ft_strequal(tmp, line))
					break ;
			ft_putstr_fd(line, file);
			ft_strdel(&line);
		}
		else
			program_errors(p, "HEREDOC", true);
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
/*
static void	valid_command(t_pipex *p, int argc, char **argv)
{
	char	**cmd_args;
	int		i;
	char	*err;

	i = 1;
	if (p->mode == PIPE)
		i = 1;
	else if (p->mode == HERE_DOC)
		i = 2;
	while (++i < argc - 1)
	{
		cmd_args = ft_split(argv[i], ' ');
		err = ft_strjoin("COMMAND ", cmd_args[0]);
		check_path_variable(p, cmd_args, err);
		ft_strdel(&err);
		ft_strarray_clear(&cmd_args);
	}
}

static void	check_path_variable(t_pipex *p, char **args, char *err)
{
	char	*cmd_path;
    char    *cmd_path_full;
	int		i;

	i = -1;
	while (p->env_paths[++i])
	{
        cmd_path = ft_strjoin(p->env_paths[i], "/");
		cmd_path_full = ft_strjoin(cmd_path, args[0]);
        ft_strdel(&cmd_path);
		if (access(cmd_path_full, X_OK) != -1)
		{
			ft_strdel(&cmd_path_full);
			break ;
		}
		ft_strdel(&cmd_path_full);
	}
	if (!p->env_paths[i])
	{
		usage_error(p, err, false);
		ft_strdel(&err);
		ft_strarray_clear(&args);
		usage_error(p, "EXIT", true);
	}
}
*/