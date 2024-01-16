/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:58:54 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/16 15:56:30 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_here_doc_put_in(t_data *data, char **av)
{
	char	*ret;

	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 2);
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0
			&& ft_strlen(av[2]) == ft_strlen(ret) - 1)
		{
			free(ret);
			return ;
		}
		ft_putstr_fd(ret, data->f1);
		free(ret);
	}
}

int	ft_access(void)
{
	int	i;

	i = 0;
	while (1)
	{
		if (access(ft_strjoin(".here_doc", ft_itoa(i)), F_OK) == -1)
			break ;
		else
			i++;
	}
	return (i);
}

void	ft_here_doc(t_data *data, char **av, char **envp, int i)
{
	i = ft_access();
	data->itoa = ft_strjoin(".here_doc", ft_itoa(i));
	data->f1 = open(ft_strjoin(".here_doc", ft_itoa(i)),
			O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->f1 < 0)
		return ;
	data->f2 = open(av[data->ac - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (data->f2 < 0)
		return ;
	if (pipe(data->pipe_fd[0]) == -1)
	{
		close(data->f2);
		close(data->f1);
	}
	ft_here_doc_put_in(data, av);
	close(data->f1);
	data->f1 = open(data->itoa, O_RDONLY);
	unlink(data->itoa);
	free(data->itoa);
	if (data->ac == 6)
		main_pipex_bonus_2(av, envp, data, 3);
	main_2(av, envp, data);
	exit(EXIT_SUCCESS);
}

void	main_here_doc(t_data *data, char **av, char **envp, int i)
{
	data->nb_pipe = data->ac - 5;
	data->j = 3;
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
	ft_here_doc(data, av, envp, 0);
}
