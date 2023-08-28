/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:22:42 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/10 02:29:52 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char	**tab, char ***env)
{
	int	i;
	int	j;

	i = 0;
	if (!tab || strcmp(tab[i], "export"))
		return (0);
	if (tab[++i] == NULL)
		return (printf("\n"), 1);
	while (tab && tab[i])
	{
		if (strchr(tab[i], '='))
		{
			j = 0;
			while (tab[i] && tab[i][j] != '\0' && tab[i][j] != '=')
			{
				if ((i == 0 && !ft_isalpha_(tab[i][0])) || (!ft_isalpha_(tab[i][j])
						&& !ft_isdigit(tab[i][j]) && tab[i][j] != '='))
				{
					printf("export: `%s': not a valid identifier\n", tab[i]);
					break ;
				}
				j++;
			}
			if (tab[i][j] != '\0' && tab[i][j] == '=')
				ft_add_to_env(tab[i], env);
		}
		i++;
	}
	return (1);
}
