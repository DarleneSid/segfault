/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 03:41:15 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/05 00:21:00 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	int		i;
	char	**monenv;
	char	**tab;

	(void)ac;
	(void)av;
	i = 0;
	monenv = ft_copy(env);
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
		if (!check_quote(str))
		{
			free(str);
			continue ;
		}
		str = ft_space(str);
		printf("%s\n", str);
		check_quote(str);
		printf("%s\n", str);
		if (!str)
			return (0);
		if (!ft_synthax(str))
		{
			free(str);
			printf(SYNTAXERROR);
			continue ;
		}
		tab = ft_split_isspace(str);
		ft_echo(tab);
		ft_export(tab, &monenv);
		free(str);
		ft_freetab(tab);
	}
	free(str);
	ft_freetab(monenv);
}
