/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:17:03 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 02:00:22 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_space(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (ft_strchr("<>|", str[i]))
		{
			count += 2;
			while (str[i] && ft_strchr("<>|", str[i]))
				i++;
		}
		else
			i++;
	}
	return (count + i);
}

char	*ft_space(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	new = ft_calloc(count_space(str) + 1, 1);
	if (!new)
		return (NULL);
	while (str && *str)
	{
		if (ft_strchr("<>|", *str))
		{
			new[i++] = ' ';
			while (*str && ft_strchr("<>|", *str))
				new[i++] = *str++;
			new[i++] = ' ';
		}
		else
			new[i++] = *str++;
	}
	return (free(tmp), new);
}
