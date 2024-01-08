/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:21:20 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/08 06:14:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "path=", 5))
		i++;
	return (&envp[i][5]);
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


/*void	ft_close(t_data *data, int i)
{
	printf("test    %d\n", i);
	if (i >= 0)
		//close(data->f1);
	if (i >= 1)
		//close(data->f1);
	//close(data->f2);
	if (i >= 2)
	{
		//close(data->f1);
		//close(data->f2);
		//close(data->pipe_fd[0]);
	}
	if (i >= 3)
		//close(data->f1);
	//close(data->f2);
	//close(data->pipe_fd[0]);
	//close(data->pipe_fd[1]);
}*/
