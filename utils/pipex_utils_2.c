#include "../pipex.h"

void	parse_prog_args(t_pipex *pipex)
{
	if (find_space(pipex->cmd_1))
	{
		pipex->cmd_1_arg = ft_split(pipex->cmd_1, ' ');
		pipex->cmd_1 = strdup(pipex->cmd_1_arg[0]);
	}
	else
	{
		pipex->cmd_1_arg = (char **)calloc(sizeof(char *), 2);
		pipex->cmd_1_arg[0] = strdup(pipex->cmd_1);
	}
	if (find_space(pipex->cmd_2))
	{
		pipex->cmd_2_arg = ft_split(pipex->cmd_2, ' ');
		pipex->cmd_2 = strdup(pipex->cmd_2_arg[0]);
	}
	else
	{
		pipex->cmd_2_arg = (char **)calloc(sizeof(char *), 2);
		pipex->cmd_2_arg[0] = strdup(pipex->cmd_2);
	}
}

void	open_files(t_pipex *pipex)
{
	int32_t	fd_one;
	int32_t	fd_two;

	fd_one = open(pipex->file1, O_CREAT | O_RDWR);
	fd_two = open(pipex->file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_one == -1 || fd_two == -1)
		handle_errors(pipex);
	pipex->fd_1_file = fd_one;
	pipex->fd_2_file = fd_two;
}
