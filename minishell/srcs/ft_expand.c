/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:09:08 by pferreir          #+#    #+#             */
/*   Updated: 2023/08/01 03:18:09 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

• Handle ’ (single quote) which should prevent the shell from interpreting 
the metacharacters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting 
the metacharacters in the quoted sequence except for $ (dollar sign).

• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values

• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline

*/