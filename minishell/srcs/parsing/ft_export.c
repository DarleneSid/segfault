/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:55:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 22:47:09 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_str(char *str, char ***env)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = ft_strlen(str);
	start = 0;
	while (i < len)
	{
		while (i < len && ft_isspace(str[i]))
			i++;
		if (i + 7 < len && !strncmp("export", &str[i], 7))
			i += 7;
		if (ft_isalpha_(str[i]))
		{
			start = i;
			i++;
			while (i < len && str[i] != '=')
			{
				if (ft_isspace(str[i]))
					break ;
				i++;
			}
			if (i < len && str[i] == '=')
			{
				i++;
				while (i < len && !ft_isspace(str[i]))
					i++;
				env = ft_add_to_env(str, start, i, env);
			}
		}
		i++;
	}
	return (1);
}

int	ft_export(char	**str, char ***env)
{
	size_t		len;
	size_t		i;
	size_t		j;

	j = 0;
	while (str && str[j])
	{
		i = 0;
		len = ft_strlen(str[j]);
		while (i < len)
		{
			if (i + 9 < len && (i == 0 || (i > 0 && ft_isspace(str[j][i - 1])))
				&& !strncmp("export", &str[j][i], 6) && ft_isspace(str[j][i + 6]))
			{
				i += 7;
				export_str(&str[j][i], env);
				break ;
			}
			i++;
		}
		j++;
	}
	return (1);
}
