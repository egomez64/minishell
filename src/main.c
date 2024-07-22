/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:19:02 by egomez            #+#    #+#             */
/*   Updated: 2024/07/22 12:43:08 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig;

static int	check_invalid(t_minishell *minishell, char *line)
{
	int	i;

	if (line[0] == '\0' || !check_quotes(line)
		|| (ft_strlen(line) == 2 && ft_strcmp(line, "\"\"") == 0))
	{
		free(line);
		(*minishell).n_line++;
		return (0);
	}
	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (1);
		i++;
	}
	if (line[i] == 0)
	{
		free(line);
		(*minishell).n_line++;
		return (0);
	}
	return (1);
}

static	int	prompt(t_minishell	*minishell, char **line)
{
	*line = NULL;
	*line = readline("minishell: ");
	signal(SIGINT, SIG_IGN);
	if (*line == NULL)
	{
		write(2, "exit\n", 6);
		free_minishell(minishell);
		return (0);
	}
	if (**line)
		add_history(*line);
	return (1);
}

static int	handle_minishell(t_minishell *minishell, t_token **tokens)
{
	(*minishell).commands = cmd(*tokens);
	expand_var(minishell, minishell->exit_status);
	red_treatment(minishell);
	if (!minishell->commands->arguments || minishell->commands->exit_s)
	{
		minishell->exit_status = minishell->commands->exit_s;
		close_mini_fds(minishell->commands);
		cmd_clear(&minishell->commands);
		return (minishell->exit_status);
	}
	(*minishell).exit_status = execution(&(*minishell));
	cmd_clear(&(*minishell).commands);
	(*minishell).n_line++;
	return (minishell->exit_status);
}

static void	parsing_error(t_token *tokens, char *line, int *exit_status)
{
	write(2, "syntax error !\n", 16);
	token_clear(tokens);
	*exit_status = 2;
	free (line);
}

int	main(int ac, char **av, char **ep)
{
	t_token		*tokens;
	char		*line;
	t_minishell	minishell;

	init_minishell(&minishell, ac, av, ep);
	while (1)
	{
		g_sig = 0;
		signal(SIGINT, &normal_c);
		signal(SIGQUIT, SIG_IGN);
		if (!prompt(&minishell, &line))
			return (minishell.exit_status);
		if (!check_invalid(&minishell, line))
			continue ;
		tokens = lexer(line);
		if (tokens && !parsing(&tokens))
		{
			parsing_error(tokens, line, &minishell.exit_status);
			continue ;
		}
		minishell.exit_status = handle_minishell(&minishell, &tokens);
		free (line);
	}
}
