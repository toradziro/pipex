#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>

# define MALLOC_ERROR -1
# define WRONG_ARGS_AMOUNT -2
# define WRONG_FILES -3
# define WRONG_PROG -4
# define FATAL_ERROR -5

typedef struct	s_pipex {
	int8_t	fd_1_file;
	int8_t	fd_2_file;
	char	*cmd_1;
	char	*cmd_2;
	char	*file1;
	char	*file2;
	char	**cmd_1_arg;
	char	**cmd_2_arg;
	char	**path;
}				t_pipex;

char	**ft_split(char *s, char c);
char	*ft_substr(char const *s, unsigned int start, int32_t len);
int8_t check_files(char *file_one, char *file_two);
int32_t	ft_strncmp(const char *s1, const char *s2, int32_t n);
void	find_path(char **env, t_pipex *pipex);
char	*ft_strjoin(char *s1, char *s2);
int8_t	find_prog(t_pipex *pipex, char **prog);
int8_t	find_space(char *str);
void	parse_prog_args(t_pipex *pipex);
void	handle_errors(int32_t err_code);
void	open_files(t_pipex *pipex);
void	start_pipex(t_pipex *pipex, int32_t *pipefd);

#endif
