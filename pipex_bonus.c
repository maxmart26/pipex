/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:19:47 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/15 18:59:11 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child(t_data *data, char **av, char **envp, int i)
{
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_in);
	close(data->fd_out);
	if (get_path(data, envp, av, i) == NULL)
	{
		ft_putstr_fd("pipex: command not found child \n", 2);
		close(data->fd_in);
		close(data->fd_out);
		exit(0);
	}
	exec(data, envp);
}

void	exec(t_data *data, char **envp)
{
	execve(data->path_def, data->mycmdargs, envp);
	ft_free_tab(data->mycmdargs);
	close(data->fd_in);
	close(data->fd_out);
	ft_free_tab(data->path);
	exit(0);
}

void	ft_parent(t_data *data, char **av, char **envp)
{
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_in);
	close(data->fd_out);
	if (get_path(data, envp, av, data->ac - 2) == NULL)
	{
		ft_putstr_fd("pipex: command final not found ici parents \n", 2);
		close(data->fd_in);
		close(data->fd_out);
		exit(0);
	}
	exec(data, envp);
}

char	*get_path(t_data *data, char **envp, char **av, int j)
{
	int	i;

	i = 0;
	data->mycmdargs = ft_split(av[j], ' ');
	data->path_from_envp = ft_path(envp);
	data->path = ft_split(data->path_from_envp, ':');
	while (data->path[i])
	{
		data->path_temp = ft_strjoin(data->path[i], "/");
		data->path_def = ft_strjoin(data->path_temp, data->mycmdargs[0]);
		free(data->path_temp);
		if (access(data->path_def, 0) == 0)
			return (data->path_def);
		else
		{
			free(data->path_def);
		}
		i++;
	}
	ft_free_tab(data->mycmdargs);
	ft_free_tab(data->path);
	return (NULL);
}

void	main_2(char **av, char **envp, t_data *data)
{
	int	k = 0;
	while (data->i < data->nb_pipe)
	{
		//printf("test avec %d et %d\n",data->i,data->j);
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
		{
			//printf("la %d\n", data->i);
			ft_close_useless(data);
			ft_child(data, av, envp, data->i + data->j);

		}
		data->i++;
		k++;
	}
	while(k > 1)
	{
		wait(0);
		k--;
	}
	// printf("la %d\n",data->i);
	ft_close_useless(data);
	ft_parent(data, av, envp);
}
void	ft_here_doc_put_in(t_data *data, char **av)
{
	char	*ret;

	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 2);
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			return ;
		}
		ft_putstr_fd(ret, data->f1);
		free(ret);
	}
}

void	ft_here_doc(t_data *data, char **av, char **envp)
{
	data->f1 = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->f1 < 0)
		return ;
	data->f2 = open(av[data->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->f2 < 0)
		return ;
	if (pipe(data->pipe_fd[0]) == -1)
	{
		close(data->f2);
		close(data->f1);
	}
	ft_here_doc_put_in(data, av);
	close(data->f1);
	data->f1 = open(".here_doc", O_RDONLY);
	main_2(av, envp, data);
	exit(EXIT_SUCCESS);
}
int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;

	i = 0;
	data.i = 0;
	data.j = 2;
	data.ac = ac;
	data.nb_pipe = ac - 4;
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		data.nb_pipe = ac - 5;
		data.j = 3;
		data.pipe_fd = malloc(data.nb_pipe * sizeof(int *));
		if (!data.pipe_fd)
			return (EXIT_FAILURE);
		while (data.nb_pipe > i)
		{
			data.pipe_fd[i] = malloc(2 * sizeof(int));
			if (pipe(data.pipe_fd[i]) == -1)
			{
				close(data.f1);
				close(data.f2);
				i--;
				while (i >= 0)
				{
					close(data.pipe_fd[i][0]);
					close(data.pipe_fd[i][1]);
					i--;
				}
				return (-1);
			}
			i++;
			// if fermer les pipes deja ouverte
		}
		ft_here_doc(&data, av, envp);
	}
	if (ac < 6)
		return (0);
	data.f1 = open(av[1], O_RDONLY);
	if (data.f1 < 0)
		return (-1);
	data.f2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.f2 < 0)
	{
		close(data.f1);
		return (-1);
	}
	data.pipe_fd = malloc(data.nb_pipe * sizeof(int *));
	if (!data.pipe_fd)
		return (EXIT_FAILURE);
	while (data.nb_pipe > i)
	{
		data.pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(data.pipe_fd[i]) == -1)
		{
			close(data.f1);
			close(data.f2);
			i--;
			while (i >= 0)
			{
				close(data.pipe_fd[i][0]);
				close(data.pipe_fd[i][1]);
				i--;
			}
			return (-1);
		}
		i++;
		// if fermer les pipes deja ouverte
	}
	main_2(av, envp, &data);
	return (0);
}
