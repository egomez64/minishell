/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:51 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 17:23:29 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	ft_isspace(int c)
// {
// 	return (c == ' ' || (c > 8 && c < 14));
// }
// 
	// while (ft_isspace(*nptr))
	// 	nptr++;

static long	nptr_to_number(int sign, const char *nptr, int *err)
{
	long	number;

	while (*nptr >= '0' && *nptr <= '9')
	{
		number *= 10;
		number += sign * (*nptr - '0');
		if ((sign > 0 && number < 0) || (sign < 0 && number > 0))
		{
			err = 1;
			return (0);
		}
		nptr++;
	}
	if (*nptr != '\0')
	{
		err = 1;
		return (0);
	}
	return (number);
}

static long	ft_atol(const char *nptr, int *err)
{
	int		sign;
	long	number;

	number = 0;
	if (*nptr == '-')
		sign = -1;
	else
		sign = 1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	number = nptr_to_number(sign, nptr, err);
	return (number);
}

static char	*error_message(int err, char *num)
{
	;
}

/**
 * takes the current exit_status, and exits with this exit_status.
 * if long long overflows: (exit 99999999999999999999999999999999)
 * 		"bash: exit: 9223372036854775808: numeric argument required"
 * 		exit with status 2
 * if not a number: (exit a b c)
 * 		"bash: exit: a: numeric argument required"
 * 		exit with status 2
 * if multiple arguments but first is okay:
 * 		"exit
 * 		bash: exit: too many arguments"
 * 		doesn't exit, status 1
*/

int	__exit(t_cmd *cmd, int exit_status)
{
	long	arg_status;
	int		err;

	printf("exit\n");
	err = 0;
	if (!cmd->arguments->next)
		exit(exit_status);
	arg_status = ft_atol((char *) cmd->arguments->next->content, &err);
	if (err)
	{
		error_message(2, (char *) cmd->arguments->next->content);
		exit(2);
	}
	if (cmd->arguments->next->next)
	{
		error_message(1, NULL);
		return (1);
	}
	exit_status = arg_status & 255;	// Nope, misses something.
	exit(exit_status);
}
