/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supstrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:24:45 by pferreir          #+#    #+#             */
/*   Updated: 2023/05/23 22:15:56 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*supstrjoin(char *s1, char *s2, char sep)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (ft_printf("malloc failed\n"), NULL);
	while (s1 && s1[j])
	{
		s[j] = s1[j];
		j++;
	}
	s[j++] = sep;
	while (s2 && s2[i])
	{
		s[i + j] = s2[i];
		i++;
	}
	s[i + j] = '\0';
	return (s);
}
