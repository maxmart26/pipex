/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:39:20 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/08 18:34:38 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_only_one(t_data *data)
{
	data->fd_in = data->f1;
	data->fd_out = data->f2;
}

void	ft_first_commande(t_data *data, int (*pipe_fd)[2])
{
	int	i;

	i = 0;
	data->fd_in = data->f1;
	close(data->f2);
	data->fd_out = pipe_fd[0][1];
	while (i < data->ac - 4)
	{
		if (i != 0)
			close(pipe_fd[i][1]);
		close(pipe_fd[i][0]);
		i++;
	}
}
void	ft_last_commande(t_data *data, int (*pipe_fd)[2])
{
	int	i;

	i = 0;
	data->fd_in = pipe_fd[data->ac - 5][0];
	close(data->f1);
	data->fd_out = data->f2;
	while (i < data->ac - 4)
	{
		close(pipe_fd[i][1]);
		if (i != data->ac - 5)
			close(pipe_fd[i][0]);
		i++;
	}
}

void	ft_middle_commande(t_data *data, int (*pipe_fd)[2])
{
	int	i;

	i = 0;
	close(data->f1);
	close(data->f2);
	data->fd_in = pipe_fd[data->i - 1][0];
	data->fd_out = pipe_fd[data->i][1];
	while (i < data->ac - 4)
	{
		if (i != data->i)
			close(pipe_fd[i][1]);
		if (i != data->i - 1)
			close(pipe_fd[i][0]);
		i++;
	}
}
void	ft_close_useless(t_data *data, int (*pipe_fd)[2])
{
	if (data->ac == 4)
		ft_only_one(data);
	else if (data->i == 0)
		ft_first_commande(data, pipe_fd);
	else if (data->i == data->ac - 4)
		ft_last_commande(data, pipe_fd);
	else
		ft_middle_commande(data, pipe_fd);
}
