#include "pipex.h"

static void	valid_command(t_pipex *p, int argc, char **argv);
static void	check_path_variable(t_pipex *p, char **args, char *err);
static void	check_command_paths(t_pipex *p, int argc, char **argv, char **envp);

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
	check_command_paths(p, argc, argv, envp);
}

void	check_heredoc_mode(t_pipex *p, int argc, char **argv, char **envp)
{
	p->fd_input = open("inputstream.txt", O_WRONLY | O_CREAT, 0777);
	if (p->fd_input == ERROR)
		usage_error(p, "OPENING INPUTSTREAM", true);
	p->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (p->fd_out == ERROR)
		usage_error(p, "OPENING OUTPUT FILE", true);
	p->limiter = ft_strdup(argv[2]);
	check_command_paths(p, argc, argv, envp);
}

static void	check_command_paths(t_pipex *p, int argc, char **argv, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	}
	p->env_paths = ft_split(envp[i] + 5, ':');
	valid_command(p, argc, argv);
}

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