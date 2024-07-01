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

extern int g_sig;

void	normal_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_c(int signal)
{
	g_sig = signal;

	ioctl(0, TIOCSTI, '\n');
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
