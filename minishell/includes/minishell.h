/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:36:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 21:55:38 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

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

#endif