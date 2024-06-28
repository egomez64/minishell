/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:59:15 by egomez            #+#    #+#             */
/*   Updated: 2024/06/28 14:01:25 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_signals(int signal, int exit_status)
{
	if (signal == SIGINT)
	{
		write(2, "^C\n", 4);
		return (130);
	}
	else if (signal == SIGQUIT)
	{
		// write(2, "", 1);
		// return (131);	// Unfinished
		write(2, "exit\n", 6);
		exit(exit_status);
	}
	return (0);			// Just to return something
}

// int	handle_signals(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(stderr, "^C\n", 3);
// 		return (130);
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		write(stderr, "")
// 	}
// }
