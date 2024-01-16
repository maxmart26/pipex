/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:19:47 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 15:58:06 by matorgue         ###   ########.fr       */
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
		ft_putstr_fd("pipex: command not found\n", 2);
		close(data->fd_in);
		close(data->fd_out);
		ft_free_int(data->pipe_fd, data->nb_pipe);
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
		ft_putstr_fd("pipex: command final not found\n", 2);
		close(data->fd_in);
		close(data->fd_out);
		ft_free_int(data->pipe_fd, data->nb_pipe);
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
	if (data->path_from_envp == NULL)
		erreur_path(data);
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
	init_data(&data, ac);
	if (ft_strncmp("here_doc", av[1], 8) == 0 && ft_strlen(av[1]) == 8)
		main_here_doc(&data, av, envp, i);
	if (ac < 5)
	{
		ft_putstr_fd("manque d argument\n", 2);
		return (0);
	}
	data.f1 = open(av[1], O_RDONLY);
	if (data.f1 < 0)
	{
		ft_putstr_fd("probleme avec le file1\n", 2);
		return (-1);
	}
	data.f2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.f2 < 0)
		return (-1);
	if (ac == 5)
		main_pipex_bonus_2(av, envp, &data, 2);
	main_multi(&data, i);
	main_2(av, envp, &data);
}
