#include "../pipex.h"

void	handle_errors(int32_t err_code, t_pipex *pipex)
{
	if (err_code == MALLOC_ERROR)
		write(STDERR_FILENO, "Error: malloc error\n", 20);
	else if (err_code == WRONG_ARGS_AMOUNT)
		write(STDERR_FILENO, "Error: Wrong amount of arguments\n", 33);
	else if (err_code == WRONG_FILES)
		write(STDERR_FILENO, "Error: files weren't found or can't be reached,"
			" please check file access bits\n", 78);
	else if (err_code == WRONG_PROG)
		write(STDERR_FILENO, "Error: one of programs weren't found, please, "
			"check if it exists\n", 65);
	else
		write(STDERR_FILENO, "KERNEL PANIC, ALL SYSTEMS ABOUT TO FALL "
			"DOWN\n", 45);
	free_pipe(pipex);
	exit(err_code);
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
