/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:09:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 03:18:09 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_replace(char **str, int start, char *replace)
{
	char	*new;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	end = start + 1;
	while (*str && (*str)[end] && (ft_isalpha_((*str)[end]) || ft_isdigit((*str)[end])))
		end++;
	new = malloc(sizeof(char) * (ft_strlen(*str) - end + start + ft_strlen(replace) + 1));
	while (*str && (*str)[i] && i < start)
	{
		new[i] = (*str)[i];
		i++;
	}
	while (replace && replace[j])
	{
		new[i] = replace[j];
		i++;
		j++;
	}
	j = end;
	while ((*str)[j])
	{
		new[i] = (*str)[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(*str);
	*str = new;
	return (ft_strlen(replace) + start - 2);
}

int	skip_simple_quote(char *str, int i)
{
	int	i1;
	int	bo;

	i1 = 0;
	bo = 0;
	while (str[i1])
	{
		if (str[i1] && str[i1] == '"')
		{
			bo = 1;
			i1++;
			while (str[i1] && str[i1] != '"')
			{
				i1++;
				if (i1 > i)
					break ;
			}
			if (i1 < i && str[i1] == '"')
			{
				i1++;
				bo = 0;
			}
		}
		else
			i1++;
	}
	if (str[i] && str[i] == '\'' && bo == 0)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i);
}

int	remove_expand(char **str, int start)
{
	char	*new;
	int		len;
	int		i;
	int		end;
	int		j;

	i = 0;
	end = start + 1;
	if ((*str)[end] && ft_isalpha_((*str)[end]))
	{
		while ((*str)[end] && (ft_isalpha_((*str)[end]) || ft_isdigit((*str)[end])))
			end++;
	}
	new = malloc(sizeof(char) * (ft_strlen(*str) - end + start + 2));
	while (*str && (*str)[i] && i < start)
	{
		new[i] = (*str)[i];
		i++;
	}
	j = end;
	while ((*str)[j])
	{
		new[i] = (*str)[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(*str);
	*str = new;
	return (start);
}

int	expand_is_in_env(char *str, int start, char ***env, char **replace)
{
	int		j;
	int		end;
	int		len;
	char	*check;

	j = 0;
	end = start;
	while (str[end] && (ft_isalpha_(str[end]) || ft_isdigit(str[end])))
		end++;
	end--;
	check = ft_substr(str, start, end - start + 1);
	len = ft_strlen(check);
	while ((*env)[j])
	{
		if ((*env)[j][len] && (*env)[j][len] == '='
			&& !ft_strncmp(check, (*env)[j], len))
		{
			*replace = ft_substr((*env)[j], ft_strlen(check) + 1, ft_strlen((*env)[j]));
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_expand(char	**str, char ***env)
{
	int		i;
	int		j;
	int		start;
	char	*replace;

	i = 0;
	j = 0;
	replace = 0;
	if (!str && !(*str))
		return (0);
	while ((*str)[i])
	{
		i = skip_simple_quote(*str, i);
		if ((*str)[i] && (*str)[i] == '$')
		{
			start = i;
			i++;
			if ((*str)[i] && (*str)[i] == '?')
			{
				printf("on remplace par le dernier exit status\n");
				i++;
			}
			if ((*str)[i] && expand_is_in_env(*str, start + 1, env, &replace))
			{
				i = expand_replace(str, start, replace) - 1;
			}
			else
				i = remove_expand(str, start);
		}
		else
			i++;
	}
	return (1);
}
