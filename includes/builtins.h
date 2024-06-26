/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:59:40 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 19:18:17 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>

bool	is_builtins(const char	*s);
int		handle_builtins(t_minishell *minish);

int		echo(t_cmd *cmd);

int		cd(t_cmd *cmd, t_env *envi);

int		pwd(void);

int		export(t_env *envi);
int		export_add(t_env **envi, t_list *args);
char	**sep_on_equal(char *s);

void	unset(t_env *envi, t_list *args);

int		env(t_env *envi);

int		__exit(t_list *args, int exit_status);

#endif
