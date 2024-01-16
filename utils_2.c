/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:16:00 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 14:22:00 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	main_pipex_2(char **av, char **envp, t_data *data)
{
	data->pid = fork();
	if (data->pid < 0)
		return ;
	if (data->pid == 0)
		ft_child(data, av, envp);
	waitpid(0, NULL, 0);
	ft_parent(data, av, envp);
}
