/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:23:12 by dsydelny          #+#    #+#             */
/*   Updated: 2023/09/02 01:20:36 by dsydelny         ###   ########.fr       */
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

void	free_inchildprocess(t_data *data, t_cmd *cmds)
{
	free_cmd(cmds);
	ft_freetab(data->arg);
	ft_freetab(data->split);
	ft_freetab(data->env);
	ft_freetab(data->path);
}

int	builtin(char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd")
	|| !ft_strcmp(str, "export") ||!ft_strcmp(str, "unset")
	||!ft_strcmp(str, "exit") || !ft_strcmp(str, "echo"))
		return (1);
	return (0);
}

int	call_builtin(char *str, t_cmd *cmds, char **env)
{
	if (!ft_strcmp(str, "cd"))
		return (ft_cd(cmds->arg), 1);
	else if (!ft_strcmp(str, "pwd"))
		return (ft_pwd(cmds->arg), 1);
	else if (!ft_strcmp(str, "export"))
		return (ft_export(cmds->arg, &env), 1);
	else if (!ft_strcmp(str, "unset"))
		return (ft_unset(cmds->arg, &env), 1);
	else if (!ft_strcmp(str, "exit"))
		return (ft_exit(cmds->arg, cmds->data, cmds), 1);
	else if (!ft_strcmp(str, "echo"))
		return (ft_echo(cmds->arg), 1);
	// if (!ft_strcmp(str, "env"))
	// 	ft_env(cmds->arg);
	// free_inchildprocess(cmds->data, cmds);
	else
		return (0);
}

int	child_process(t_data *data, char **tab, char **env, int i)
{
	char	**arg;
	char	*cmd;
	// t_cmd	*cmds;

	free(data->pid);
	data->arg = ft_split(tab[i], ' ');
	if (!data->arg)
		exit(1);
	if (!*data->arg)
	{
		ft_printf("bash: : command not found\n");
		return (free(data->arg), exit(1), 1);
	}
	data->cmds = parse(data->arg);
	data->cmds->data = data;
	redirection(data, data->cmds, i); 
	if (!data->cmds->cmd)
	{
		free_inchildprocess(data, data->cmds);
		exit (1);
	}
	if (builtin(data->cmds->cmd))
		call_builtin (data->cmds->cmd, data->cmds, env);
	else
	{
		cmd = check_cmd(data, env, data->cmds->arg);
		if (cmd)
			execve(cmd, data->cmds->arg, env);
		the_perror(data->cmds->cmd);
		free(cmd);
	}
	free_inchildprocess(data, data->cmds);
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

int    ft_strlen_tab(char **tab)
{
    int    i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void	execution(t_data *data, char **tab, char **env)
{
	int	i;
	char *cmd;
	

	i = 0;
	printf("[[[[[[[%s]]]]]]]\n", tab[0]);
	data->nbcmd = count_len(tab);
	data->arg = ft_split(tab[0], ' ');
	if (!data->arg)
		exit(1);
	if (!*data->arg)
	{
		ft_printf("bash: : command not found\n");
		free(data->arg);
		exit(1);
	}
	data->cmds = parse(data->arg);
	data->cmds->data = data;
	if (data->nbcmd == 1 && builtin(data->cmds->cmd))
	{
		printf("i am builtin %s\n", tab[0]);
		call_builtin(data->cmds->cmd, data->cmds, env);
	}
	else
	{
		free_cmd(data->cmds);
		ft_freetab(data->arg);
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
}
