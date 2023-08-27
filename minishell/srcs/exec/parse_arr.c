/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:39:30 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/26 20:48:50 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_of_arr(char *s)
{
	if (!ft_strcmp(">", s))
		return (1);
	else if (!ft_strcmp(">>", s))
		return (2);
	else if (!ft_strcmp("<", s))
		return (3);
	else if (!ft_strcmp("<<", s))
		return (4);
	return (0);
}

void	mallocall(t_cmd	*cmds, char **tab)
{
	int	i;
	int	t;
	int	a;

	i = 0;
	t = 0;
	a = 0;
	while (tab[i])
	{
		if (type_of_arr(tab[i]))
		{
			t++;
			i++;
		}
		else
		{
			a++;
			i++;
		}
	}
	cmds->arg = ft_calloc(sizeof(char *), a + 1);
	cmds->file = ft_calloc(sizeof(char *), t + 1);
	cmds->type = ft_calloc(sizeof(int), t);
}

void	print_cmd(t_cmd *cmds)
{
	int	i;

	if (cmds->cmd)
		fprintf(stderr, "CMD NAME = {%s}\n", cmds->cmd);
	i = 0;
	while (cmds->arg[i])
		fprintf(stderr, "[%s]", cmds->arg[i++]);
	fprintf(stderr, "\n");
	i = 0;
	while(cmds->file[i])
	{
		fprintf(stderr,"{%i}[%s]\n", cmds->type[i], cmds->file[i]);
		i++;
	}
}

t_cmd	parse(char **tab)
{
	t_cmd	cmds;
	int		i;
	int		t;
	int		a;

	i = 0;
	t = 0;
	a = 0;
	mallocall(&cmds, tab);
	while (tab[i])
	{
		if (type_of_arr(tab[i]))
		{
			cmds.type[t] = type_of_arr(tab[i]);
			cmds.file[t++] = tab[i + 1];
			i++;
		}
		else
			cmds.arg[a++] = tab[i];
		i++;
	}
	cmds.cmd = cmds.arg[0];
	print_cmd(&cmds);
	return (cmds);
}
