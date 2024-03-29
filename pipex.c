/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:44:07 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 16:03:42 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(t_data *data, char **av, char **envp)
{
	dup2(data->f1, STDIN_FILENO);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->f1);
	close(data->f2);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (get_path(data, envp, av, 2) == NULL)
	{
		ft_putstr_fd("pipex: command 1 not found \n", 2);
		close(data->f1);
		close(data->f2);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		exit(0);
	}
	exec(data, envp);
}

void	exec(t_data *data, char **envp)
{
	execve(data->path_def, data->mycmdargs, envp);
	ft_free_tab(data->mycmdargs);
	close(data->f1);
	close(data->f2);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	ft_free_tab(data->path);
	exit(0);
}

void	ft_parent(t_data *data, char **av, char **envp)
{
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->f2, STDOUT_FILENO);
	close(data->f1);
	close(data->f2);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (get_path(data, envp, av, 3) == NULL)
	{
		ft_putstr_fd("pipex: command 2 not found \n", 2);
		close(data->f1);
		close(data->f2);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
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

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5)
	{
		ft_putstr_fd("pas assez ou trop d arguments\n", 2);
		return (0);
	}
	data.f1 = open(av[1], O_RDONLY);
	if (data.f1 < 0)
	{
		ft_putstr_fd("probleme avec le file 1\n", 2);
		return (-1);
	}
	data.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.f2 < 0)
	{
		ft_putstr_fd("probleme avec le file 2", 2);
		return (-1);
	}
	if (pipe(data.pipe_fd) == -1)
		return (-1);
	main_pipex_2(av, envp, &data);
	return (0);
}
