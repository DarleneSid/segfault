/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:33:06 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 03:02:34 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int		i;
	int		bo;
	char	c;

	i = 0;
	bo = 1;
	while (str && str[i])
	{
		if (str && str[i] == DQUOTE || str[i] == SQUOTE)
		{
			c = str[i];
			bo = 0;
			i++;
			while (str[i] && str[i] != c)
			{
				str[i] *= -1;
				i++;
			}
			if (!str[i])
				return (bo);
			if (str[i] == c)
				bo = 1;
		}
		i++;
	}
	return (bo);
}

int	check_rafter(char *str, int i)
{
	if (str[i] && ft_strchr("<>|", str[i]))
	{
		if (str[i + 1] && !ft_strncmp(&str[i], "<<", 2)
			|| !ft_strncmp(&str[i], ">>", 2))
			i += 1;
		i++;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			return (0);
		if (!ft_strchr("<>|", str[i]))
			return (i + 1);
		return (0);
	}
	return (i + 1);
}

int	ft_synthax(char *str)
{
	int	i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (0);
	while (str && str[i])
	{
		i = check_rafter(str, i);
		if (i == 0)
			return (0);
	}
	return (1);
}
