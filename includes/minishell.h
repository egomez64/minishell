/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:40:26 by egomez            #+#    #+#             */
/*   Updated: 2024/06/24 14:40:15 by maamine          ###   ########.fr       */
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

typedef struct s_minishell
{
	t_cmd				*commands;
	t_env				*envi;
}					t_minishell;

#endif