#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_pipex {
	char	**cmd_1_arg;
	char	**cmd_2_arg;
	char	**path;
	char	*cmd_1;
	char	*cmd_2;
	char	*file1;
	char	*file2;
	int32_t	fd_1_file;
	int32_t	fd_2_file;
	int8_t	is_first_cmd;
	int8_t	is_second_cmd;
}				t_pipex;

char	**ft_split(char *s, char c);
char	*ft_substr(char const *s, unsigned int start, int32_t len);
void	find_path(char **env, t_pipex *pipex);
char	*ft_strjoin(char *s1, char *s2);
int8_t	find_prog(t_pipex *pipex, char **prog);
int8_t	find_space(char *str);
void	parse_prog_args(t_pipex *pipex);
void	handle_errors(t_pipex *pipex);
void	open_files(t_pipex *pipex);
int32_t	start_pipex(t_pipex *pipex, int32_t *pipefd, char **envp);
void	free_pipe(t_pipex *pipex);
void	free_db_arr(char **arr);

#endif
