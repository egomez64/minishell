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

#include <stdbool.h>

typedef struct s_env
{
	char	*name;
	char	*val;
	bool	init;
	struct s_env *next;
}   t_env;

t_env	*env_new(char	*var_name, char *var_val, bool state);
t_env	*env_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
void	env_clear(t_env	*lst);
int		env_size(t_env *env);
t_env   *get_env(char **env_var);
int		is_env(char *s);
t_list  *split_in_lst(char *s);
void    changes(t_list *lst, t_env *envi, int exit_status);
char    *join_lst(t_list *lst);
void    handle_word(char *s, t_env *envi, t_list **new, int exit_status);
void	expand_var(t_cmd *commands, t_env **env_var, int exit_status);
char	*ft_strjoin_char(char *s1, char c, bool free_data);
bool    is_delimiter(char c);
t_list	*ft_lstnew_empty();
char    *supp_quotes(char *join);
char    *slash_quotes(char *arg);
int		how_many_q(char *arg);
bool    is_whitespace(char c);
t_list  *split_on_whitespace(char *s);
int		expand_red(t_token *red, t_env *env, int exit_status);
void	handle_heredoc(char *s, int *fd, int *exit_s);
void    fill_file(int fd, char *s);
void    randomizer(char *str);
void	red_treatment(t_cmd **cmd);
void	handle_output(char *path, int *fd, int *exit_s);
void	handle_append(char *path, int *fd, int *exit_s);
void	handle_input(char *path, int *fd, int *exit_s);

# endif