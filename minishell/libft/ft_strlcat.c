/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:24:28 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/25 21:20:39 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	i;

	len_d = ft_strlen(dst);
	i = 0;
	if (size <= len_d)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && i + len_d < size - 1)
	{
		dst[i + len_d] = src[i];
		i++;
	}
	dst[i + len_d] = '\0';
	return (len_d + ft_strlen(src));
}

void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
}
