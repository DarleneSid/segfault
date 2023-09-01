/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:24:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/07/28 00:21:15 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup1(char *str, char c)
{
	char	*mot;
	int		i;
	int		taille_mot;

	taille_mot = 0;
	i = 0;
	while (str[taille_mot] != '\0' && str[taille_mot] != c)
		taille_mot++;
	mot = (char *)malloc((taille_mot + 1) * sizeof(char));
	if (mot == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
	{
		mot[i] = str[i];
		i++;
	}
	mot[i] = 0;
	return (mot);
}

static int	countwords(char *str, char c)
{
	int	nb_mot;

	nb_mot = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			nb_mot++;
		}
		while (*str && *str != c)
			str++;
	}
	return (nb_mot);
}

char	**do_split(char *str, char c, int nb)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(nb + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (str && *str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			tab[i] = ft_strdup1(str, c);
			if (tab[i] == NULL)
				return (ft_freetab(tab), NULL);
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	return (tab);
}

char	**ft_split(char *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	if (!str)
		return (NULL);
	nb = countwords(str, c);
	if (!nb)
		return (NULL);
	return (do_split(str, c, nb));
}
