/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/26 21:05:01 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data = {0};
	char	*str;
	int		i;
	char	**monenv;
	char	**tab;

	(void)ac;
	(void)av;
	i = 0;
	data.env = ft_copy(env);
	while (1)
	{
		str = readline("pao> ");
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		// if (!check_quote(str))
		// {
		// 	free(str);
		// 	continue ;
		// }
		// str = ft_space(str);
		// printf("%s\n", str);
		// check_quote(str);
		// printf("%s\n", str);
		// if (!str)
		// 	return (0);
		// if (!ft_synthax(str))
		// {
		// 	free(str);
		// 	printf(SYNTAXERROR);
		// 	continue ;
		// }
		// tab = ft_split_isspace(str);
		tab = ft_split(str, '|');
		execution(&data, tab, env);
		// ft_echo(tab);
		// ft_export(tab, &data.env);
		free(str);
		ft_freetab(tab);
	}
	free(str);
	ft_freetab(data.env);
}
