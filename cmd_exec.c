#include "pipex.h"

static char	*parse_path(t_pipex *p, char *cmd);
static char	*find_command(char *cmd, char **paths);

void    exec_cmd(t_pipex *p, char *full_cmd)
{
	char	**cmd;
	char	*full_path;

	if (!*full_cmd)
		program_errors(p, "NO CMD", true);
	cmd = ft_split(full_cmd, ' ');
	if (!cmd)
		program_errors(p, "SPLIT", true);
	if (cmd[0] && ft_strchr(cmd[0], '/'))
		full_path = cmd[0];
	else
		full_path = parse_path(p, cmd[0]);
	if (access(full_path, F_OK) == ERROR)
			program_errors(p, "NO CMD", true);
	else
	{
	if (execve(full_path, cmd, p->envp) == ERROR)
		program_errors(p, "NO CMD", true);
	}
}

static char	*parse_path(t_pipex *p, char *cmd)
{
	char	**paths;
	size_t	i;

	i = 0;
	while (p->envp[i] && ft_strncmp(p->envp[i], "PATH=", 5))
		i++;
	if (!p->envp[i])
		return (NULL);
	paths = ft_split(p->envp[i] + 5, ':');
	if (!paths)
		program_errors(p, "SPLIT", true);
	return (find_command(cmd, paths));
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