#include "pipex.h"

static char	*find_command(char *cmd, char **paths);

void	child_process(t_pipex *p, int cmd)
{
	p->pid_cmd = fork();
	if (p->pid_cmd == ERROR)
		program_errors(p, "FORK", true);
	if (p->pid_cmd == CHILD_PROCESS)
	{
		if (cmd == 0)
			dup2_util(p, p->fd_input, p->pipes[0 + WRITE_END]);
		else if (cmd == p->n_cmds - 1)
			dup2_util(p, p->pipes[2 * cmd - 2], p->fd_output);
		else
			dup2_util(p, p->pipes[2 * cmd - 2], p->pipes[2 * cmd + WRITE_END]);
		close_pipes(p);
		p->cmd_args = ft_split(p->argv[p->mode + cmd], ' ');
		p->cmd = find_command(p->cmd_args[0], p->env_paths);
		if (!p->cmd || access(p->cmd, F_OK) == ERROR)
			program_errors(p, p->cmd_args[0], true);
		execve(p->cmd, p->cmd_args, p->envp);
	}
}

static char	*find_command(char *cmd, char **paths)
{
	char	*path;
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		ft_strdel(&tmp);
		if (access(path, F_OK) == 0)
		{
			ft_strarray_clear(&paths);
			return (path);
		}
		else
			ft_strdel(&path);
		i++;
	}
	ft_strarray_clear(&paths);
	return (NULL);
}
