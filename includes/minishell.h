/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:40:26 by egomez            #+#    #+#             */
/*   Updated: 2024/07/04 17:55:46 by maamine          ###   ########.fr       */
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

void	free_achar(char **achar);

#endif