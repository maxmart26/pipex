/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:21:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 16:03:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		pipefd[2];
	int		**pipe_fd;
	int		nb_pipe;
	char	*itoa;
	int		ac;
	int		i;
	int		j;
	int		fd_in;
	int		fd_out;
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
void		ft_close_useless(t_data *data);
void		ft_free_int(int **tab, int j);
void		main_here_doc(t_data *data, char **av, char **envp, int i);
void		ft_here_doc(t_data *data, char **av, char **envp, int i);
void		ft_here_doc_put_in(t_data *data, char **av);
void		main_2(char **av, char **envp, t_data *data);
void		main_multi(t_data *data, int i);
void		ft_child(t_data *data, char **av, char **envp, int i);
void		erreur_path(t_data *data);
void		ft_parent(t_data *data, char **av, char **envp);
void		init_data(t_data *data, int ac);
void		main_pipex_bonus_2(char **av, char **envp, t_data *data, int i);
char		*get_path_for_1(t_data *data, char **envp, char **av, int j);
void		ft_parent_for_1(t_data *data, char **av, char **envp);
void		exec_for_1(t_data *data, char **envp);
void		ft_child_for_1(t_data *data, char **av, char **envp, int i);

#endif
