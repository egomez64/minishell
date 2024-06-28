/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:59:15 by egomez            #+#    #+#             */
/*   Updated: 2024/06/28 03:59:20 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		write(stderr, "^C\n", 3);
		return (130);
	}
	else if (signal == SIGQUIT)
	{
		write(stderr, "")
	}
}