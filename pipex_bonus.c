/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:19:47 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/08 18:38:38 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child(t_data *data, char **av, char **envp)
{
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_in);
	close(data->fd_out);
	if (get_path(data, envp, av, 2) == NULL)
	{
		ft_putstr_fd("pipex: command not found \n", 2);
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
	if (get_path(data, envp, av, 3) == NULL)
	{
		ft_putstr_fd("pipex: command final not found \n", 2);
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

void	main_2(char **av, char **envp, t_data *data, int (*pipe_fd)[2])
{
	while (data->i < data->ac - 4)
	{
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
		{
			ft_close_useless(data, pipe_fd);
			ft_child(data, av, envp);
			waitpid(0, NULL, 0);
		}
		data->i++;
	}
	ft_close_useless(data, pipe_fd);
	ft_parent(data, av, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;
	int		pipe_fd[ac - 4][2];

	i = 0;
	data.i = 0;
	data.ac = ac;
	if (ac < 5)
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
	while(ac - 4 > i)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			close(data.f1);
			close(data.f2);
			i--;
			while (i >= 0)
			{
				close(pipe_fd[i][0]);
				close(pipe_fd[i][1]);
				i--;
			}
			return (-1);
		}
		i++;
		//if fermer les pipes deja ouverte
	}
	main_2(av, envp, &data, pipe_fd);
	return (0);
}



