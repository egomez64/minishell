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

int	main(int ac, char **av, char **ep)
{
	t_token		*tmp;
	char		*line;
	t_minishell	minishell;
	(void)		ac;
	(void)		av;

	// open_debug(3);
	init_minishell(&minishell);
	minishell.envi = envp_to_lst(ep);
	minishell.exit_status = 0;
	minishell.n_line = 1;
	// g_sig = 0;
	while(1)
	{
		g_sig = 0;
		// line = readline("minishell> ");
		signal(SIGINT, &normal_c);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		signal(SIGINT, SIG_IGN);// Just for the tester
		if (line == NULL)
		{
			// free_minishell(&minishell);
			write(2, "exit\n", 6);
			free_minishell(&minishell);
			return (minishell.exit_status);
		}
		if (line[0] == '\0')
		{
			free(line);
			minishell.n_line++;
			continue ;
		}
		add_history(line);
		if (!check_quotes(line))
		{
			minishell.n_line++;
			continue ;
		}
		tmp = lexer(line);
		if (tmp && !parsing(&tmp))
		{
			write(2, "syntax error !\n", 16);
			token_clear(tmp);
			minishell.exit_status = 2;
			continue ;
		}
		minishell.commands = cmd(tmp);
		expand_var(&minishell, minishell.exit_status);
		red_treatment(&minishell);
		minishell.exit_status = execution(&minishell);
		// token_clear(tmp);

		cmd_clear(&minishell.commands);
		free(line);
		minishell.n_line++;
	}
	free_minishell(&minishell);
	return (0);
}
