/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:44:09 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/25 21:16:11 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_path(t_data *data, char *cmd)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	while (data->path && data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		new = ft_strjoin(tmp, cmd);
		if (access(new, F_OK | X_OK) != -1)
			return (new);
		free(tmp);
		free(new);
		i++;
	}
	return (NULL);
}
