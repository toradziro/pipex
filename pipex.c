#include "pipex.h"

void	start_pipex(t_pipex *pipex, int32_t *pipefd)
{
	pid_t	child;

	child = fork();
	if (child > 0)
	{
		close(pipefd[0]);
		dup2(pipex->fd_1_file, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		execve(pipex->cmd_1, pipex->cmd_1_arg, pipex->path);
		waitpid(child, NULL, 0);
	}
	else if (child == 0)
	{
		child = fork();
		if (child > 0)
		{
			close(pipefd[1]);
			dup2(pipex->fd_2_file, STDOUT_FILENO);
			dup2(pipefd[0], STDIN_FILENO);
			execve(pipex->cmd_2, pipex->cmd_2_arg, pipex->path);
			waitpid(child, NULL, 0);
		}
	}
	else if (child == -1)
		handle_errors(FATAL_ERROR);
}

void	init_pipex(char **argv, t_pipex *pipex, char **env)
{
	int32_t	*pipefd;

	find_path(env, pipex);
	pipex->cmd_1 = argv[2];
	pipex->cmd_2 = argv[3];
	pipex->file1 = argv[1];
	pipex->file2 = argv[4];
	parse_prog_args(pipex);
	pipefd = (int32_t*)malloc(sizeof(int32_t) * 2);
	if (!pipefd)
		handle_errors(MALLOC_ERROR);
	if (find_prog(pipex, &pipex->cmd_1) || find_prog(pipex, &pipex->cmd_2))
		handle_errors(WRONG_PROG);
	open_files(pipex);
	pipe(pipefd);
	start_pipex(pipex, pipefd);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	pipex = (t_pipex*)malloc(sizeof(t_pipex) * 1);
	if (!pipex)
		handle_errors(MALLOC_ERROR);
	if (argc != 5)
		handle_errors(WRONG_ARGS_AMOUNT);
	check_files(argv[1], argv[4]);
	init_pipex(argv, pipex, env);
	close(pipex->fd_1_file);
	close(pipex->fd_2_file);
	free(pipex);
	return (0);
}
