/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:40:26 by egomez            #+#    #+#             */
/*   Updated: 2024/07/22 12:35:20 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <parsing.h>
# include <expand.h>
# include <exec.h>
# include <builtins.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct s_minishell
{
	t_cmd	*commands;
	t_env	*envi;
	int		exit_status;
	int		n_line;
}			t_minishell;

void	init_minishell(t_minishell *minishell, int ac, char **av, char **ep);
void	close_mini_fds(t_cmd *cmd);
void	free_minishell(t_minishell *minishell);

void	free_achar(char **achar);

void	str_error_message(char *name, char *err);

int		str_skip_to_char(char *str, char c);
int		str_skip_to_any_char(char *str, char *targets);

#endif