
#ifndef PIPEX_H
# define PIPEX_H

#include "./libft/libft.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_data
{
	int		pipe_fd[2];
	char	*path_temp;
	int		bools;
	char	*path_def;
	char	*path_from_envp;
	char	**path;
	char	**mycmdargs;
	int		pid;
	int		pid2;
	int		f1;
	int		f2;
}			t_data;


char	*ft_path(char **envp);
void	ft_free_tab(char **tab);
void	exec(t_data *data, char **envp);
void	ft_close(t_data *data,int i);
char	*get_path(t_data *data,char **envp, char **av, int j);

#endif