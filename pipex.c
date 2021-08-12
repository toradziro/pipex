#include "pipex.h"

pid_t	executor(t_pipex *pipex, int32_t *pipefd, int8_t flag, char **envp)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		if (flag == 0)
		{
			close(pipefd[0]);
			dup2(pipex->fd_1_file, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			execve(pipex->cmd_1, pipex->cmd_1_arg, envp);
			exit(errno);
		}
		if (flag == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			dup2(pipex->fd_2_file, STDOUT_FILENO);
			execve(pipex->cmd_2, pipex->cmd_2_arg, envp);
			exit(errno);
		}
	}
	else if (child == -1)
		handle_errors(pipex);
	return (child);
}

void	start_pipex(t_pipex *pipex, int32_t *pipefd, char **envp)
{
	executor(pipex, pipefd, 0, envp);
	executor(pipex, pipefd, 1, envp);
}

void	init_pipex(char **argv, t_pipex *pipex, char **envp)
{
	int32_t	*pipefd;

	find_path(envp, pipex);
	pipex->cmd_1 = strdup(argv[2]);
	pipex->cmd_2 = strdup(argv[3]);
	pipex->file1 = strdup(argv[1]);
	pipex->file2 = strdup(argv[4]);
	parse_prog_args(pipex);
	pipefd = (int32_t *)calloc(sizeof(int32_t), 2);
	if (!pipefd)
		handle_errors(pipex);
	if (find_prog(pipex, &pipex->cmd_1) || find_prog(pipex, &pipex->cmd_2))
		handle_errors(pipex);
	open_files(pipex);
	pipe(pipefd);
	start_pipex(pipex, pipefd, envp);
	free(pipefd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)calloc(sizeof(t_pipex), 1);
	if (!pipex)
		handle_errors(pipex);
	if (argc != 5)
		handle_errors(pipex);
	init_pipex(argv, pipex, envp);
	free_pipe(pipex);
	return (0);
}
