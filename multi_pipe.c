/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:11:47 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 15:57:25 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	main_multi(t_data *data, int i)
{
	data->pipe_fd = malloc(data->nb_pipe * sizeof(int *));
	if (!data->pipe_fd)
		exit(0);
	while (data->nb_pipe > i)
	{
		data->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(data->pipe_fd[i]) == -1)
		{
			close(data->f1);
			close(data->f2);
			i--;
			while (i >= 0)
			{
				close(data->pipe_fd[i][0]);
				close(data->pipe_fd[i][1]);
				i--;
			}
			exit(0);
		}
		i++;
	}
}

void	main_2(char **av, char **envp, t_data *data)
{
	int	k;

	k = 0;
	while (data->i < data->nb_pipe && data->nb_pipe != 1)
	{
		data->pid = fork();
		if (data->pid < 0)
			return ;
		if (data->pid == 0)
		{
			ft_close_useless(data);
			ft_child(data, av, envp, data->i + data->j);
		}
		data->i++;
		k++;
	}
	while (k >= data->nb_pipe)
	{
		wait(0);
		k--;
	}
	ft_close_useless(data);
	ft_parent(data, av, envp);
}

void	main_pipex_bonus_2(char **av, char **envp, t_data *data, int i)
{
	if (pipe(data->pipefd) == -1)
		exit (0);
	data->pid = fork();
	if (data->pid < 0)
		return ;
	if (data->pid == 0)
		ft_child_for_1(data, av, envp, i);
	waitpid(0, NULL, 0);
	ft_parent_for_1(data, av, envp);
}
