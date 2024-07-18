/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:51 by maamine           #+#    #+#             */
/*   Updated: 2024/07/04 17:48:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static char	*error_message(int err, char *num)
{
	char	*join1;
	char	*join2;

	if (err == 1)
		write(2, "minishell: exit: too many arguments\n", 37);
	else if (err == 2)
	{
		join1 = ft_strjoin("bash: exit: ", num);
		join2 = ft_strjoin(join1, ": numeric argument required\n");
		write(2, join2, ft_strlen(join2));
		free(join1);
		free(join2);
	}
	return (NULL);
}

int	__exit(t_list *args, int exit_status)
{
	long	arg_status;
	int		err;

	write(2, "exit\n", 6);
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
	exit_status = arg_status & 0xff;
	exit(exit_status);
}
