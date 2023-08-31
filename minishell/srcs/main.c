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
			printf("empty input\n");
			continue ;
		}
		add_history(str);
		str = ft_space(str);
		ft_expand(&str, &monenv);
		if (!check_quote(str))
		{
		 	free(str);
			printf("quote error\n");
		 	continue ;
		}
		str = remove_useless_quote(str);
		if (str[0] == 0)
		{
			free(str);
			printf("no string\n");
			continue ;
		}
		if (!ft_syntax(str))
		{
			free(str);
			printf("syntax error\n");
			continue ;
		}
		if (str)
			tab = ft_split_isspace(str);
		ft_unquote(tab, &monenv);
		ft_echo(tab);
		ft_export(tab, &monenv);
		ft_unset(tab, &monenv);
		if (tab && !strncmp(tab[0], "env", 3))
			printtab(monenv);
		//tab = ft_split(str, '|');
		//execution(&data, tab, env);
		// ft_echo(tab);
		// ft_export(tab, &data.env);
		free(str);
		ft_freetab(tab);
	}
	free(str);
	ft_freetab(data.env);
}
