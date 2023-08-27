/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:01:49 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/27 23:08:27 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "miishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9' )
		return (0);
	else
		return (1);
}

long long int	ft_atoi(const char *nptr)
{
	long long int	n;
	int	i;
	int	signe;
	int	c;

	n = 0;
	i = 0;
	signe = 1;
	c = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-' )
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		c = nptr[i] - '0';
		n = 10 * n + c;
		i++;
	}
	return (n * signe);
}

int	ft_exit(char **tab)
{
	int	i;
	long long int	num;

	i = 0;
	if (!tab || strncmp(tab[i], "exit", 4))
		return (0);
	if (!strncmp(tab[i], "exit", 4) && !tab[i + 1])
	{
		printf("exit\n");
		exit (0);
	}
	if ((!strncmp(tab[i], "exit", 4) && tab[i + 1] && !tab[i + 2]))
	{
		num = ft_atoi(tab[i + 1]);
		if (num >= 0 && num <= 9223372036854775807)
		{
			printf("exit\n");
			exit(num % 256);
		}
		else if (num > 9223372036854775807)
		{
			printf("exit\n");
			printf("bash: exit: %lld: numeric argument required\n", num);
			exit (2);
		}
		else if (num < 0)
		{
			printf("exit\n");
			printf ("%lld\n", num);
			num = -num;
			//exit(num % 256);
		}
	}
	else if ((!strncmp(tab[i], "exit", 4) && tab[i + 1] && tab[i + 2]))
	{
		num = ft_atoi(tab[i + 1]);
		if (num == 0)
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", tab[i + 1]);
			exit (2);
		}
		else if (num > 0 && num <= 9223372036854775807)
		{
			printf("exit\n");
			printf("bash: exit: too many arguments\n");
		}
	}
	printf("NO EXIT\n");
	return (0);
}

// int main()
// {
// 	// char *tab1[50] = {"exit", "12", NULL}; // 
// 	// char *tab2[50] = {"exit", "9223372036854775807", NULL}; // 
// 	// char *tab3[50] = {"exit", "9223372036854775808", NULL}; // 
// 	//char *tab4[50] = {"exit", NULL}; //
// 	// char *tab5[50] = {"exit", "abc", "12", NULL}; //
// 	char *tab6[50] = {"exit", "-12", NULL}; //
	
// 	// ft_exit(tab1);
// 	// ft_exit(tab2);
// 	//ft_exit(tab3);
// 	//ft_exit(tab4);
// 	// ft_exit(tab5);
// 	ft_exit(tab6);	
// }
