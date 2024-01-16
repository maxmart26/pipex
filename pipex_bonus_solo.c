/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_solo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:35:05 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 15:52:35 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child_for_1(t_data *data, char **av, char **envp, int i)
{
	dup2(data->f1, STDIN_FILENO);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->f1);
	close(data->f2);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (get_path_for_1(data, envp, av, i) == NULL)
	{
		ft_putstr_fd("pipex: command 1 not found \n", 2);
		close(data->f1);
		close(data->f2);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		exit(0);
	}
	exec_for_1(data, envp);
}

void	exec_for_1(t_data *data, char **envp)
{
	execve(data->path_def, data->mycmdargs, envp);
	ft_free_tab(data->mycmdargs);
	close(data->f1);
	close(data->f2);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	ft_free_tab(data->path);
	exit(0);
}

void	ft_parent_for_1(t_data *data, char **av, char **envp)
{
	dup2(data->pipefd[0], STDIN_FILENO);
	dup2(data->f2, STDOUT_FILENO);
	close(data->f1);
	close(data->f2);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (get_path_for_1(data, envp, av, 3) == NULL)
	{
		ft_putstr_fd("pipex: command 2 not found \n", 2);
		close(data->f1);
		close(data->f2);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		exit(0);
	}
	exec_for_1(data, envp);
}

char	*get_path_for_1(t_data *data, char **envp, char **av, int j)
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
