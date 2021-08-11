#include "../pipex.h"

void	handle_errors(t_pipex *pipex)
{
	printf("%s\n", strerror(errno));
	free_pipe(pipex);
	exit(errno);
}

void	free_db_arr(char **arr)
{
	int32_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

void	free_pipe(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->fd_1_file != -1)
			close(pipex->fd_1_file);
		if (pipex->fd_2_file != -1)
			close(pipex->fd_2_file);
		if (pipex->cmd_1)
			free(pipex->cmd_1);
		if (pipex->cmd_2)
			free(pipex->cmd_2);
		if (pipex->file1)
			free(pipex->file1);
		if (pipex->file2)
			free(pipex->file2);
		if (pipex->cmd_1_arg)
			free_db_arr(pipex->cmd_1_arg);
		if (pipex->cmd_2_arg)
			free_db_arr(pipex->cmd_2_arg);
		if (pipex->path)
			free_db_arr(pipex->path);
		free(pipex);
	}
}
