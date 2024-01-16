/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:21:17 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 16:03:25 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

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

char		*ft_path(char **envp);
void		ft_free_tab(char **tab);
void		exec(t_data *data, char **envp);
void		ft_close(t_data *data, int i);
char		*get_path(t_data *data, char **envp, char **av, int j);
void		main_pipex_2(char **av, char **envp, t_data *data);
void		ft_parent(t_data *data, char **av, char **envp);
void		ft_child(t_data *data, char **av, char **envp);
void		main_pipex_2(char **av, char **envp, t_data *data);

#endif
