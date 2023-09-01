/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/09/01 02:23:43 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"
// # include "../ft_printf/ft_printf.h"


# define SQUOTE '\''
# define DQUOTE '\"'
# define SYNTAXERROR "syntax error !\n"

int		check_quote(char *str);
int		check_rafter(char *str, int i);
int		ft_synthax(char *str);

int		count_space(char *str);
char	*ft_space(char *input);

char	**ft_copy(char **env);
int		replace_in_env(char **tmp, char *add, char ***env);
char	***ft_add_to_env(char *str, int start, int end, char ***env);
char	***ft_remove_from_env(char *str, int start, int end, char ***env);

void	ft_unquote(char *str);
int		ft_export(char	**str, char ***env);

int		ft_unset(char	**str, char ***env);
int		unset_str(char *str, char ***env);

int		check_echo_option(char *str);
int		ft_echo(char **tab);
int		ft_cd(char **tab);



typedef struct t_data {
	int		nbcmd;
	int		fd[2];
	int		prev_pipe;
	char	**env;
	char	**path;
	int		*pid;
	int		exit_code;
	char	**arg;
	char	**split;
	struct t_cmd	*cmds;
}		t_data;

typedef	struct t_cmd {
	char	*cmd;
	char	**arg;
	int		*type; // < >> >
	char	**file;
	struct t_data	*data;
}		t_cmd;

int		ft_exit(char **tab, t_data *data, t_cmd *cmds);
void	call_builtin(char *str, t_cmd *cmds, char **env);
int		builtin(char *str);
void	free_inchildprocess(t_data *data, t_cmd *cmds);
int		ft_pwd(char **tab);
// tab = {<}{infile1}{wc}{-l}{>}{out1}{>>}{append1}{<<}{heredoc1}{-c}{>}{out2}{>>}{append2}{<}{infile2}
// t_cmds =
// 	cmd = "wc";
// 	arg = {"wc", "-l", "-c", NULL};
// 	type = {3,			1,		2,			4,			1,		2,			3};
// 	file = {"infile1",	out1,	append1,	heredoc1,	out2,	append2,	infile2}

// infile  infile2
// outfile append2
// execve()

// tab = {cat}{-e}{>}{out}
// t_cmds = 
// 	cmd	= "cat"
// 	arg = {"cat", "-e", NULL};
// 	type = {1};
// 	file = {out};

// tab = {<}{infile}
// 	cmd = NULL;
// 	arg = NULL;
// 	type = {3};
// 	file = {infile};
	
// tab = {> cat -e out}
// 	cmd = "-e";
// 	arg = {"-e", "out", NULL};
// 	type = {1};
// 	file = {cat};
	
// tab = {cat -e out}
// 	cmd = "cat"
// 	arg = {"cat", "-e", "out", NULL};
// 	type = NULL;
// 	file = NULL;
	

// after type always file
// if tab[i] == type
// 	type[k] = typeof(tab[i]);
// 	file[k] = tab[i + 1]
// 	i++;
// else
// 	arg[p] = tab[i++];

// >	1
// >>	2
// <	3
// <<	4

/*		EXEC PATH 		*/
char	**get_path(char **env);
char	*find_path(t_data *data, char *cmd);

/*		EXEC PIPEX		*/
void	init(t_data *data, int ac, char **av);
int		child_process(t_data *data, char **av, char **env, int i);
void	parent_process(t_data *data);
void	wait_n_close(t_data *data);
void	execution(t_data *data, char **tab, char **env);

/*		EXEC ERROR 		*/
void	the_perror(char *str);
void	close_n_exit(t_data *data, char *str);
void	dup_n_close(int fd1, int fd2);
void	ft_freetab(char **tab);

/*		EXEC UTILS 		*/
void	redirection(t_data *data, t_cmd *cmds, int index);
char	*check_cmd(t_data *data, char **env, char **tab);

int		type_of_arr(char *s);
void	mallocall(t_cmd	*cmds, char **tab);
t_cmd	*parse(char **tab);
void	free_cmd(t_cmd *cmds);

#endif
