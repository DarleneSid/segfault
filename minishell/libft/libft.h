/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:21:22 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/25 21:20:55 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

size_t			ft_strlen(const char *s);
int				ft_atoi(const char *nptr);
void			*ft_bzero(void *ptr, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *ptr, int x, size_t n);
char			**ft_split(char *str, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strtrim(char const *s1, char const *s2);
char			*ft_strjoin(char *s1, char *s2);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_freetab(char **tab);
char			*ft_realloc(char *s1, char *s2);
int				ft_printf(const char *format, ...);
int				ft_putchar(char c);
int				ft_putstr(char *s);
int				ft_putnbr(int nb);
char			*supstrjoin(char *s1, char *s2, char sep);
int				ft_hexa(unsigned long nb, int s);
int				ft_unsigned_int(unsigned int nb);
void			print(char c, va_list pr, int *i);
int				ft_strcmp(char *str1, char *str2);
int				ft_pointer(unsigned long n);
int				ft_isalpha_(int c);
int				ft_isspace(int c);
char			**ft_split_isspace(char *str);
char			**do_split_isspace(char *str, int nb);

void	ft_strcat(char *dst, const char *src);


#endif
