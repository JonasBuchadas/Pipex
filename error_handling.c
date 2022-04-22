#include "pipex.h"

void	usage_error(t_pipex *p, char *usage_name, bool stop)
{
	if (ft_strequal(usage_name, "USAGE"))
	{
		ft_putendl_fd("Not enough arguments given.", 2);
		ft_putstr_fd(usage_name, 2);
		ft_putstr_fd(": ./pipex \"filename of file 1\"", 2);
		ft_putstr_fd(" \"n Commands (with flags or args)\"", 2);
		ft_putstr_fd(" \"filename of file 2\"\n", 2);
	}
	else if (ft_strequal(usage_name, "HERE_DOC MODE USAGE"))
	{
		ft_putendl_fd("Not enough arguments given.", 2);
		ft_putstr_fd(usage_name, 2);
		ft_putstr_fd(": ./pipex \"here_doc\"", 2);
		ft_putstr_fd(" \"n Commands (with flags or args)\"", 2);
		ft_putstr_fd(" \"filename of file 2\"\n", 2);
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
