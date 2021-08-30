#include "pipex.h"

int32_t wait_proccess(pid_t pid, t_pipex *pipex)
{
	int32_t status;

	status = 0;
	if (pid > 0)
		status = waitpid(pid, NULL, WUNTRACED | WNOHANG | WCONTINUED);
	if (pid < 0)
		handle_errors(pipex);
	return (status);
}

int32_t executor(t_pipex *pipex, int32_t *pipefd, int8_t flag, char **envp)
{
	pid_t	child;
	int32_t	res;

	child = fork();
	res = 0;
	if (child == 0)
	{
		if (flag == 0)
		{
			close(pipefd[0]);
			dup2(pipex->fd_1_file, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			if (execve(pipex->cmd_1, pipex->cmd_1_arg, envp) == -1)
				handle_errors(pipex);
			exit(errno);
		}
		if (flag == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			dup2(pipex->fd_2_file, STDOUT_FILENO);
			if (execve(pipex->cmd_2, pipex->cmd_2_arg, envp) == -1)
				handle_errors(pipex);
			exit(errno);
		}
	}
	res = wait_proccess(child, pipex);
	return (res);
}

int32_t	start_pipex(t_pipex *pipex, int32_t *pipefd, char **envp)
{
	int32_t	res;

	res = 0;
	if (!pipex->is_first_cmd)
		executor(pipex, pipefd, 0, envp);
	if (!pipex->is_second_cmd)
		res = executor(pipex, pipefd, 1, envp);
	return (res);
}

int32_t init_pipex(char **argv, t_pipex *pipex, char **envp)
{
	int32_t	*pipefd;
	int32_t	res;

	res = 0;
	find_path(envp, pipex);
	pipex->cmd_1 = strdup(argv[2]);
	pipex->cmd_2 = strdup(argv[3]);
	pipex->file1 = strdup(argv[1]);
	pipex->file2 = strdup(argv[4]);
	parse_prog_args(pipex);
	pipefd = (int32_t *)calloc(sizeof(int32_t), 2);
	if (!pipefd)
		handle_errors(pipex);
	pipex->is_first_cmd = find_prog(pipex, &pipex->cmd_1);
	pipex->is_second_cmd = find_prog(pipex, &pipex->cmd_2);
	if (pipex->is_first_cmd && pipex->is_second_cmd)
		handle_errors(pipex);
	open_files(pipex);
	pipe(pipefd);
	res = start_pipex(pipex, pipefd, envp);
	free(pipefd);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int32_t	res;

	pipex = (t_pipex *)calloc(sizeof(t_pipex), 1);
	if (!pipex)
		handle_errors(pipex);
	if (argc != 5)
		handle_errors(pipex);
	res = init_pipex(argv, pipex, envp);
	free_pipe(pipex);
	return (res);
}
