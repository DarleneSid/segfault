/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:23:12 by mgamil            #+#    #+#             */
/*   Updated: 2023/08/25 21:15:43 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data, int ac, char **tab)
{
	data->pid = malloc(sizeof(int) * ac);
	if (!data->pid)
		exit(1);
	data->prev_pipe = -1;
	data->path = NULL;
}

// ls > out | cat -e

int	type_of_arr(char *s)
{
	if (!ft_strcmp(">", s))
		return(1);
	else if (!ft_strcmp(">>", s))
		return(2);
	else if (!ft_strcmp("<", s))
		return(3);
	else if (!ft_strcmp("<<", s))
		return(4);
	return (0);
}

void	mallocall(t_cmd	*cmds, char **tab)
{
	int i;
	int	t;
	int a;

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
	if (cmds->cmd)
		fprintf(stderr, "CMD NAME = {%s}\n", cmds->cmd);
	int i = 0;
	while(cmds->arg[i])
		fprintf(stderr,"[%s]",cmds->arg[i++]);
	fprintf(stderr, "\n");
	i = 0;
	while(cmds->file[i])
	{
		fprintf(stderr,"{%i}[%s]\n", cmds->type[i], cmds->file[i]);
		i++;
	}

}

t_cmd 	parse(char **tab)
{
	t_cmd cmds;

	int i;
	int	t;
	int a;

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
		{
			cmds.arg[a++] = tab[i];
		}
		i++;
	}
	cmds.cmd = cmds.arg[0];
	print_cmd(&cmds);
	return (cmds);
}

int	child_process(t_data *data, char **tab, char **env, int i)
{
	char	**arg;
	char	*cmd;

	free(data->pid);
	arg = ft_split(tab[i], ' ');
	if (!arg)
		exit(1);
	if (!*arg)
	{
		ft_printf("bash: : command not found\n");
		return (free(arg), exit(1), 1);
	}
	t_cmd cmds = parse(arg);
	redirection(data, &cmds, i);
	cmd = check_cmd(data, env, cmds.arg);
	execve(cmd, cmds.arg, env);
	the_perror(arg[0]);
	free(cmd);
	ft_freetab(arg);
	ft_freetab(data->path);
	exit(127);
}

void	parent_process(t_data *data)
{
	close(data->fd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	data->prev_pipe = data->fd[0];
}

void	wait_n_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd)
		waitpid(data->pid[i++], 0, 0);
	close(data->fd[0]);
	free(data->pid);
}

int		count_len(char **tab)
{
	int	i;

	i = 0;
	while(tab && tab[i])
		i++;
	return (i);
}

void	print_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
	{
		printf("[%i]{%s}\n", i, tab[i]);
	}
}


void	execution(t_data *data, char **tab, char **env)
{
	int	i;

	i = 0;

	data->nbcmd = count_len(tab);
	init(data, data->nbcmd, tab);
	while (i < data->nbcmd)
	{
		pipe(data->fd);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			child_process(data, tab, env, i);
		else if (data->pid[i] > 0)
			parent_process(data);
		i++;
	}
	wait_n_close(data);
}
