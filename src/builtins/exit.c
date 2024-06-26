/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:51 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 19:11:03 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	nptr_to_number(int sign, const char *nptr, int *err)
{
	long	number;

	number = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		number *= 10;
		number += sign * (*nptr - '0');
		if ((sign > 0 && number < 0) || (sign < 0 && number > 0))
		{
			*err = 1;
			return (0);
		}
		nptr++;
	}
	if (*nptr != '\0')
	{
		*err = 1;
		return (0);
	}
	return (number);
}

static long	ft_atol(const char *nptr, int *err)
{
	int		sign;

	if (*nptr == '-')
		sign = -1;
	else
		sign = 1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	return (nptr_to_number(sign, nptr, err));
}

static char	*error_message(int err, char *num)	// 
{
	(void) err;
	(void) num;
	return (NULL);
}

int	__exit(t_list *args, int exit_status)
{
	long	arg_status;
	int		err;

	printf("exit\n");
	err = 0;
	if (!args->next)
		exit(exit_status);
	arg_status = ft_atol((char *) args->next->content, &err);
	if (err)
	{
		error_message(2, (char *) args->next->content);
		exit(2);
	}
	if (args->next->next)
	{
		error_message(1, NULL);
		return (1);
	}
	exit_status = arg_status & 255;	// Nope, misses something. Maybe.
	exit(exit_status);
}
