#include "../pipex.h"

int8_t	find_space(char *str)
{
	int32_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		++i;
	}
	return (0);
}

int8_t	check_files(char *file_one, char *file_two)
{
	int32_t	check_one;
	int32_t	check_two;

	check_one = access(file_one, R_OK | W_OK);
	check_two = access(file_two, R_OK | W_OK);
	if (check_one || check_two)
		handle_errors(WRONG_FILES);
	return (1);
}

void	find_path(char **env, t_pipex *pipex)
{
	int32_t	i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			pipex->path = ft_split(&(env[i][5]), ':');
			return ;
		}
		++i;
	}
}

int8_t	find_prog(t_pipex *pipex, char **prog)
{
	int32_t i;
	char	*tmp;

	i = 0;
	if (!strncmp(*prog, "./", 2) || !strncmp(*prog, "../", 3))
		return (0);
	while (pipex->path[i])
	{
		tmp = ft_strjoin(strdup(pipex->path[i]), "/");
		tmp = ft_strjoin(tmp, *prog);
		if (!access(tmp, X_OK))
		{
			*prog = tmp;
			return (0);
		}
		++i;
	}
	return (1);
}
