/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:19:27 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/01 01:16:45 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef PATH_MAX
# define PATH_MAX	10000
#endif

int	ft_pwd(char **tab)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (path[0])
		return (printf("%s\n", path), 0);
	return (1);
}
