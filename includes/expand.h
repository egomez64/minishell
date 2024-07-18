/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:19:38 by egomez            #+#    #+#             */
/*   Updated: 2024/07/03 18:11:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>
# include <minishell.h>

typedef struct s_minishell	t_minishell;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

t_env	*env_new(char	*var_name, char *var_val/*, bool init*/);
t_env	*env_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
void	env_clear(t_env	*lst);
int		env_size(t_env *env);
t_env	*envp_to_lst(char **env_var);
int		is_env(char *s);

void	handle_word(char *s, t_env *envi, t_list **new, int exit_status);

void	expand_var(t_minishell *minishell, int exit_status);

char	*ft_strjoin_char(char *s1, char c, bool free_data);
bool	is_delimiter(char c);
t_list	*ft_lstnew_empty(void);
char	*supp_quotes(char *join);
char	*slash_quotes(char *arg);
bool	is_whitespace(char c);

void	handle_heredoc(char *s, int *fd, int *exit_s, int n_line);
void	red_treatment(t_minishell *minishell);
// void	handle_output(char *path, int *fd, int *exit_s);
// void	handle_append(char *path, int *fd, int *exit_s);
// void	handle_input(char *path, int *fd, int *exit_s);

#endif