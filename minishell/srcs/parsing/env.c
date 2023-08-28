/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:57:23 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/10 02:48:08 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy(char **env)
{
	int		n;
	int		i;
	char	**cpenv;

	n = 0;
	i = 0;
	while (env && env[n])
		n++;
	cpenv = ft_calloc(n + 1, sizeof(char *));
	while (i < n)
	{
		cpenv[i] = ft_strdup(env[i]);
		i++;
	}
	return (cpenv);
}

int	replace_in_env(char *add, char ***env)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (ft_strlen_tab(*env) == 0)
		return (1);
	while (add[i] != '=')
		i++;
	while ((*env)[j])
	{
		if ((*env)[j][i] && !ft_strncmp(add, (*env)[j], i))
		{
			free((*env)[j]);
			(*env)[j] = ft_strdup(add);
			return (0);
		}
		j++;
	}
	return (j);
}

void	ft_add_to_env(char *add, char ***env)
{
	int		i;
	char	**new;
	int		len;

	i = 0;
	len = replace_in_env(add, env);
	if (!len)
		return ;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return ;
	while (env && *env && (*env)[i])
	{
		new[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new[i] = ft_strdup(add);
	free(*env);
	*env = new;
}

void	ft_remove_from_env(char *remove, char ***env)
{
	int		i;
	int		j;
	char	**new;
	int		len;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen_tab(*env), sizeof(char *));
	if (!new)
		return ;
	while (env && (*env) && (*env)[i])
	{
		if (strcmp((*env)[i], remove))
		{
			new[j++] = ft_strdup((*env)[i]);
		}
		free((*env)[i]);
		i++;
	}
	free(*env);
	*env = new;
}
