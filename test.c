 #include <minishell.h>

static int	open_debug(int newfd)
{
	int	fd;

	fd = open("debug", O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	if (fd == newfd)
		return (0);
	if (dup2(fd, newfd) != newfd)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	t_token		*tmp;
	char		*line;
	t_minishell	minishell;
	(void)		ac;
	(void)		av;

	open_debug(3);
	init_minishell(&minishell);
	minishell.envi = get_env(ep);
	minishell.exit_status = 0;
	while(1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			free_minishell(&minishell);
			return (0);
		}
		if (line[0] == 0)
		{
			free(line);
			continue;
		}
		add_history(line);
		if (!check_quotes(line))
		{
			printf("problems with quotes, a quotes should be open\n");
			continue;
		}
		tmp = lexer(line);
		if (!parsing(&tmp))
		{
			write(2, "syntax error !\n", 16);
			return (2);
		}
		dprintf(3, "good syntax\n");
		minishell.commands = cmd(tmp);
		expand_var(&minishell, minishell.exit_status);
		red_treatment(&minishell);
		minishell.exit_status = execution(&minishell);
		token_clear(tmp);

		cmd_clear(minishell.commands);
		free(line);
	}
    free_minishell(&minishell);
	return (0);
}
