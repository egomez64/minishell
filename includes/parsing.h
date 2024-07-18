/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:43:07 by egomez            #+#    #+#             */
/*   Updated: 2024/07/18 16:49:13 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum arg_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}	t_arg;

// const static char * arg_to_string[] = { // 
// 	[WORD] = "Word",
// 	[PIPE] = "Pipe",
// 	[INPUT] = "INPUT",
// 	[OUTPUT] = "OUTPUT",
// 	[HEREDOC] = "HEREDOC",
// 	[APPEND] = "APPEND",
// };

typedef struct s_token
{
	t_arg			type;
	char			*val;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	t_list			*arguments;
	t_token			*redirections;
	int				exit_s;
	int				input_fd;
	int				output_fd;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell	t_minishell;

t_token	*token_new(char	*val, t_arg type);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *new);
int		check_quotes(char *s);
void	skip(char *s, int *i);
int		tokenize_word(t_token **tok_lst, char *val);
int		tokenize_symbol(t_token **tok_lst, char *val);
t_token	*lexer(char *arg);
int		redirect_tester(t_token **token);
int		pipe_tester(t_token **token);
int		parsing(t_token **token);
void	token_clear(t_token	*token);
void	cmd_clear(t_cmd	**cmd);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*cmd_last(t_cmd *lst);
t_cmd	*cmd_new(void);
t_list	*lstnew(char *val);
t_list	*lstlast(t_list *lst);
void	lstadd_back(t_list **lst, t_list *new);
void	lstdelone(t_list *lst);
void	lstclear(t_list **lst);
t_cmd	*cmd(t_token *token);
void	free_minishell(t_minishell *minishell);
void	init_minishell(t_minishell *minishell);

#endif