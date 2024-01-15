/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:39:20 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/15 19:20:11 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_only_one(t_data *data)
{
	ft_putstr_fd("only one\n",2);
	data->fd_in = data->f1;
	data->fd_out = data->f2;
}

void	ft_first_commande(t_data *data)
{
	int	i;

	i = 0;
	ft_putstr_fd("ici first\n",2);
	data->fd_in = data->f1;
	close(data->f2);
	data->fd_out = data->pipe_fd[0][1];
	while (i < data->nb_pipe)
	{
		if (i != 0)
			close(data->pipe_fd[i][1]);
		close(data->pipe_fd[i][0]);
		i++;
	}
}
void	ft_last_commande(t_data *data)
{
	int	i;

	i = 0;
	ft_putstr_fd("ici last\n",2);
	//printf("ici last\n");
	//printf("ici le pipe %d\n",data->nb_pipe - 1);
	data->fd_in = data->pipe_fd[data->nb_pipe - 1][0];
	close(data->f1);
	data->fd_out = data->f2;
	while (i < data->nb_pipe)
	{
		close(data->pipe_fd[i][1]);
		if (i != data->nb_pipe - 1)
			close(data->pipe_fd[i][0]);
		i++;
	}
}

void	ft_middle_commande(t_data *data)
{
	int	i;

	i = 0;
	ft_putstr_fd("ici middle\n",2);
	data->fd_out = data->pipe_fd[data->i][1];
	data->fd_in = data->pipe_fd[data->i - 1][0];
	close(data->f1);
	close(data->f2);
	while (i < data->nb_pipe)
	{
		//printf("ici le i %d et data %d\n",i, data->i);
		if (i != data->i)
		{
			//ft_putstr_fd("ici le normal\n",2);
			close(data->pipe_fd[i][1]);
		}
		if (i != data->i - 1)
		{
			//ft_putstr_fd("ici le - 1\n",2);
			close(data->pipe_fd[i][0]);
		}
		i++;
	}
}
void	ft_close_useless(t_data *data)
{
	//ft_putnbr_fd(data->i,2);
	if (data->nb_pipe == 1)
		ft_only_one(data);
	else if (data->i == 0)
		ft_first_commande(data);
	else if (data->i == data->nb_pipe)
		ft_last_commande(data);
	else
		ft_middle_commande(data);
}
