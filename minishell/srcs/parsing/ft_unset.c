/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:18:53 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 22:47:29 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// while (str && str[j])
	// {
	// 	i = 0;
	// 	len = ft_strlen(str[j]);
	// 	while (i < len)
	// 	{
	// 		if (i + 6 < len && (i == 0 || (i > 0 && ft_isspace(str[j][i - 1])))
	// 			&& !strncmp("unset", &	str[j][i], 5) && ft_isspace(str[j][i + 5]))
	// 		{
	// 			i += 6;
	// 			start = i;
	// 			unset_str(&str[j][i], env);
	// 			break ;
	// 		}
	// 		i++;
	// 	}
	// 	j++;
	// }

int	ft_unset(char	**str, char ***env)
{
	size_t		j;

	j = 1;
	while (str && str[j])
	{
		unset_str(str[j], env);
		j++;
	}
	return (1);
}

int	unset_str(char *str, char ***env)
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
		if (i + 6 < len && !strncmp("unset ", &str[i], 6))
			i += 6;
		if (ft_isalpha_(str[i]))
		{
			while (i < len && !ft_isspace(str[i]))
				i++;
			env = ft_remove_from_env(str, start, i, env);
		}
		i++;
	}
	return (1);
}
