/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:18:53 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/28 01:58:01 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **tab, char ***env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!tab || strcmp(tab[i], "unset") || !(*env))
		return (0);
	if (tab[++i] == NULL)
		return (1);
	while (tab && tab[i])
	{
		j = -1;
		str = ft_strjoin(tab[i], "=");
		while ((*env)[++j])
		{
			if (!strncmp((*env)[j], str, ft_strlen(str)))
			{
				free(str);
				str = strdup((*env)[j]);
				ft_remove_from_env(str, env);
				break ;
			}
		}
		free (str);
		i++;
	}
	return (1);
}
