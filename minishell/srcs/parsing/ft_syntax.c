/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:33:06 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/28 19:57:26 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int		i;
	int		bo;
	char	c;

	i = -1;
	bo = 1;
	while (str && str[++i])
	{
		if (str && str[i] == DQUOTE || str[i] == SQUOTE)
		{
			c = str[i++];
			bo = 0;
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

int	ft_syntax(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	if (str && str[i] == '|')
		return (0);
	while (str[i])
	{
		i = check_rafter(str, i);
		if (i == 0)
			return (0);
	}
	return (1);
}

char	*ft_unquote_str(char *str, int len, int *start, char c)
{
	int		k;
	int		i;
	char	*new;

	k = 0;
	i = 0;
	new = malloc(sizeof(char) * len);
	while (i < *start)
		new[k++] = str[i++];
	i++;
	while (k < len && str[i] != c)
	{
		str[i] *= -1;
		new[k++] = str[i++];
	}
	if (str[i] == c)
		*start = i - 1;
	i++;
	while (k < len && str[i])
		new[k++] = str[i++];
	new[k] = '\0';
	free (str);
	return (new);
}

void	ft_unquote(char **tab, char ***env)
{
	int		i;
	int		j;
	int		len;
	char	c;

	j = 0;
	while (tab && tab[j])
	{
		i = 0;
		len = ft_strlen(tab[j]);
		while (tab[j][i])
		{
			if (tab[j][i] == '\'' || tab[j][i] == '"')
			{
				c = tab[j][i];
				tab[j] = ft_unquote_str(tab[j], len, &i, c);
			}
			else
				i++;
		}
		j++;
	}
}
