/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:59:15 by egomez            #+#    #+#             */
/*   Updated: 2024/07/29 11:22:56 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

void	normal_c(int signal)
{
	g_sig = signal;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_c(int signal)
{
	char	c;

	g_sig = signal;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

// void	sig_exec(int wstatus)
// {
// 	int	signal;
// 
// 	signal = WTERMSIG(wstatus);
// 	if (signal == SIGINT)
// 	{
// 		normal_c(signal);
// 		printf("\n");
// 	}
// }

// int	sig_exec(int wstatus/*, bool is_last*/)
// {
// 	int	signal;
//
// 	signal = WTERMSIG(wstatus);
// 	if (signal == SIGINT)
// 	{
// 		normal_c(signal);
// 		write(2, "\n", 2);
// 		return (128 + signal);
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		// if (is_last)
// 		// 	write(2, "Quit\n", 6);
// 		return (128 + signal);
// 	}
// 	return (WEXITSTATUS(wstatus));
// }
