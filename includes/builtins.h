/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:59:40 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 15:21:22 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>

bool	is_builtins(const char	*s);
int		handle_builtins(t_cmd	*cmd, t_env **envi);

int		pwd(void);

int		env(t_env *envi);

int		export(t_env *envi);
int		export_add(t_env **envi, t_list *args);
void	print_export(t_env **envi, char **new_env);
void	free_env(char **new_env);
void	bubble_sort(char **new_env);
int		export_join(t_env *envi, char *s);
int		export_append(t_env *envi, char *s);
int		set_null(t_env *envi, char *s);
int		check_arg(char *s);

void	unset(t_env *envi, char *s);
char	**sep_on_equal(char *s);

int		echo(t_cmd *cmd);

int		cd(t_cmd *cmd, t_env *envi);

#endif
