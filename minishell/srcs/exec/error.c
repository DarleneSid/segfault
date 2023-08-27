/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:46:53 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/26 18:36:09 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_perror(char *str)
{
	char	new[1024];

	if (ft_strlen(str) > 1000)
		perror(str);
	else
	{
		ft_strlcpy(new, "bash: ", 7);
		ft_strcat(new, str);
		perror(new);
	}
}

void	close_n_exit(t_data *data, char *str)
{
	the_perror(str);
	close(data->fd[1]);
	close(data->fd[0]);
	exit(1);
}

void	dup_n_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
