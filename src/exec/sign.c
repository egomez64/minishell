/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:59:15 by egomez            #+#    #+#             */
/*   Updated: 2024/07/04 17:34:01 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

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
	char	c;

	g_sig = signal;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	sig_exec(int wstatus)
{
	int	signal;

	signal = WTERMSIG(wstatus);
	if (signal == SIGINT)
	{
		normal_c(signal);
		write(2, "\n", 2);
		return (WEXITSTATUS(wstatus));
	}
	else if (signal == SIGQUIT)
	{
		write(2, "Quit\n", 6);
		return (WEXITSTATUS(wstatus));
	}
	return (WEXITSTATUS(wstatus));
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
