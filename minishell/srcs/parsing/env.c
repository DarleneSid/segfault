/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:57:23 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 03:57:47 by pferreir         ###   ########.fr       */
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

int	replace_in_env(char **tmp, char *add, char ***env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (add[i] != '=')
		i++;
	while (tmp && tmp[len])
	{
		if (tmp[len][i] && !ft_strncmp(add, tmp[len], i))
		{
			free(tmp[len]);
			tmp[len] = ft_strdup(add);
			*env = tmp;
			return (0);
		}
		len++;
	}
	return (len);
}

char	***ft_add_to_env(char *str, int start, int end, char ***env)
{
	int		i;
	char	**new;
	char	**tmp;
	int		len;
	char	*add;

	tmp = *env;
	i = -1;
	add = ft_substr(str, start, end - start + 1);
	len = replace_in_env(tmp, add, env);
	if (!len)
		return (free(add), env);
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	while (++i < len)
	{
		new[i] = ft_strdup(tmp[i]);
		free(tmp[i]);
	}
	new[len] = ft_strdup(add);
	free(tmp);
	*env = new;
	return (free(add), env);
}

char	***ft_remove_from_env(char *str, int start, int end, char ***env)
{
	int		i;
	size_t	len_r;
	size_t	len;
	char	**new;
	char	**tmp;
	int		index;
	char	*remove;

	tmp = *env;
	index = -1;
	len = 0;
	remove = ft_substr(str, start, end - start + 1);
	len_r = end - start + 1;
	i = 0;
	while (tmp && tmp[len])
	{
		if (tmp[len][len_r] && !ft_strncmp(remove, tmp[len], len_r))
			index = len;
		len++;
	}
	if (index >= 0)
	{
		new = ft_calloc(len - 1, sizeof(char *));
		if (!new)
			return (NULL);
		while (++i < len)
		{
			if (i != index)
				new[i] = ft_strdup(tmp[i]);
			i++;
		}
		ft_freetab(tmp);
		*env = new;
	}
	return (free(remove), env);
}