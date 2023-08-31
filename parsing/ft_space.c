/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:17:03 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/28 21:28:21 by pferreir         ###   ########.fr       */
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

int count_previous_quote(char *str, int i)
{
	int	i1;
	int	count;

	i1 = 0;
	count = 0;
	while (str && i1 < i)
	{
		if (str[i1] == '"' || str[i1] == '\'')
			count++;
		i1++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	count_useless_quote(char *str)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	len = ft_strlen(str);
	count = 0;
	while (str && str[i])
	{
		if (i + 2 < len && count_previous_quote(str, i)
		&& (str[i] == '"' || str[i] == '\'') && str[i + 1] == str[i])
				i += 2;
		else if (i + 2 < len && count_previous_quote(str, i)
		&& (str[i] == '"' || str[i] == '\'') && str[i + 2] == str[i])
		{
			count += 1;
			i += 3;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*remove_useless_quote(char *str)
{
	char	*new;
	int		i;
	int		i1;
	int		len;
	int		size;

	i = 0;
	i1 = 0;
	len = count_useless_quote(str);
	size = ft_strlen(str);
	if (len == size)
		return (str);
	new = malloc(sizeof(char) * (len + 1));
	while (i1 < len && i < size)
	{
		if (i + 1 < size && count_previous_quote(str, i)
		&& (str[i] == '\'' || str[i] == '"') && str[i + 1] == str[i])
				i += 2;
		else if (i + 2 < size && count_previous_quote(str, i)
		&& (str[i] == '"' || str[i] == '\'') && str[i + 2] == str[i])
		{
			new[i1] = -str[i + 1];
			i += 3;
			i1++;
		}
		else
			new[i1++] = str[i++];
	}
	new[i1] = '\0';
	free(str);
	if (count_useless_quote(new) != len)
		remove_useless_quote(new);
	return (new);
}