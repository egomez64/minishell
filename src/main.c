/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:19:02 by egomez            #+#    #+#             */
/*   Updated: 2024/07/21 20:50:54 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int	open_debug(int newfd)
// {
// 	int	fd;
//
// 	fd = open("debug", O_RDWR | O_CREAT | O_TRUNC,
// 		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	if (fd == -1)
// 		return (-1);
// 	if (fd == newfd)
// 		return (0);
// 	if (dup2(fd, newfd) != newfd)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }
int	g_sig;

static int	check_errors(t_minishell *minishell, char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		(*minishell).n_line++;
		return (0);
	}
	if (!check_quotes(line))
	{
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

static void	init(t_minishell *minishell, int ac, char **av, char **ep)
{
	g_sig = 0;
	(void) ac;
	(void) av;
	init_minishell(&(*minishell));
	(*minishell).envi = envp_to_lst(ep);
	(*minishell).exit_status = 0;
	(*minishell).n_line = 1;
}

static void	handle_minishell(t_minishell *minishell, \
	t_token **tokens, char **line)
{
	(*minishell).commands = cmd(*tokens);
	expand_var(&(*minishell), (*minishell).exit_status);
	red_treatment(&(*minishell));
	if (!minishell->commands->arguments)
	{
		cmd_clear(&minishell->commands);
		return ;
	}
	(*minishell).exit_status = execution(&(*minishell));
	cmd_clear(&(*minishell).commands);
	free(*line);
	(*minishell).n_line++;
}

int	main(int ac, char **av, char **ep)
{
	t_token		*tokens;
	char		*line;
	t_minishell	minishell;

	init(&minishell, ac, av, ep);
	while (1)
	{
		signal(SIGINT, &normal_c);
		signal(SIGQUIT, SIG_IGN);
		if (!prompt(&minishell, &line))
			return (minishell.exit_status);
		if (!check_errors(&minishell, line))
			continue ;
		tokens = lexer(line);
		if (tokens && !parsing(&tokens))
		{
			write(2, "syntax error !\n", 16);
			token_clear(tokens);
			minishell.exit_status = 2;
			continue ;
		}
		handle_minishell(&minishell, &tokens, &line);
	}
	free_minishell(&minishell);
	return (0);
}
