/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:59:40 by maamine           #+#    #+#             */
/*   Updated: 2024/07/18 16:33:53 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>

bool	is_builtin(const char *s);
int		handle_builtin(t_cmd *cmd, t_minishell *minish, int stdfd[2]);

int		echo(t_cmd *cmd);

int		cd(t_cmd *cmd, t_env *envi);

int		pwd(void);

int		export(t_env *envi);
int		export_add(t_env **envi, t_list *args);
char	**sep_on_equal(char *s);

void	unset(t_env *envi, t_list *args);

int		env(t_env *envi);

int		__exit(t_minishell *minish, t_list *args, int stdfd[2]);

#endif
