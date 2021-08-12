#include "../pipex.h"

int8_t	find_space(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		++i;
	}
	return (0);
}

void	find_path(char **env, t_pipex *pipex)
{
	int32_t	i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			pipex->path = ft_split(getenv("PATH"), ':');
			return ;
		}
		++i;
	}
}

int8_t	find_prog(t_pipex *pipex, char **prog)
{
	int32_t	i;
	char	*tmp;

	i = 0;
	if (!strncmp(*prog, "./", 2) || !strncmp(*prog, "../", 3)
		|| !strncmp(*prog, "/", 1))
		return (0);
	while (pipex->path[i])
	{
		tmp = ft_strjoin(strdup(pipex->path[i]), "/");
		tmp = ft_strjoin(tmp, *prog);
		if (!access(tmp, X_OK))
		{
			free(*prog);
			*prog = tmp;
			return (0);
		}
		free(tmp);
		++i;
	}
	return (1);
}
