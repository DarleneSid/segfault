/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:23:12 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/26 21:04:00 by dsydelny         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmds)
{
	free(cmds->arg);
	free(cmds->type);
	free(cmds->file);
}

int	child_process(t_data *data, char **tab, char **env, int i)
{
	char	**arg;
	char	*cmd;
	t_cmd	cmds;

	free(data->pid);
	arg = ft_split(tab[i], ' ');
	if (!arg)
		exit(1);
	if (!*arg)
	{
		ft_printf("bash: : command not found\n");
		return (free(arg), exit(1), 1);
	}
	cmds = parse(arg);
	redirection(data, &cmds, i);
	cmd = check_cmd(data, env, cmds.arg);
	if (cmd)
		execve(cmd, cmds.arg, env);
	free_cmd(&cmds);
	the_perror(cmds.cmd);
	free(cmd);
	ft_freetab(arg);
	ft_freetab(tab);
	ft_freetab(data->env);
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

int	count_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
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
