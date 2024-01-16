/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:20:00 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/15 23:28:09 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_int(int **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	erreur_path(t_data *data)
{
	ft_putstr_fd("probleme avec le PATH\n", 2);
	ft_close_useless(data);
	ft_free_int(data->pipe_fd, data->nb_pipe);
	ft_free_tab(data->mycmdargs);
	close(data->fd_in);
	close(data->fd_out);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data, int ac)
{
	data->i = 0;
	data->j = 2;
	data->ac = ac;
	data->nb_pipe = ac - 4;
}
