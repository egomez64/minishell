/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:19:38 by egomez            #+#    #+#             */
/*   Updated: 2024/04/26 17:19:41 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_env
{
	char *name;
	char *val;
	struct s_env *next;
}   t_env;

t_env	*env_new(char	*var_name, char *var_val);
t_env	*env_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
void	env_clear(t_env	*lst);
t_env   *get_env(char **env_var);
t_list	*divide_lst(char *str);
void	handle_cmd(t_cmd *node, t_env *table);
void    expand_var(t_cmd *commands, t_env *env_var);
int		needed(char	*str, char *parent);
char    *valof(t_env    *lst, char  *name);
char    *node_treatment(char *str, t_env *lst);

# endif