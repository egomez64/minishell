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
	t_cmd *commands;
	t_token *tmp;
	char    *line;
	t_env	*env_var;
	int		exit_status;
	(void)ac;
	(void)av;

	open_debug(3);
	env_var = get_env(ep);
	exit_status = 0;
	while(1)
	{
		line = readline("minishell>");
		if (line == 0)
			return (0);
		add_history(line);
		tmp = lexer(line);
		if (!parsing(&tmp))
		{
			dprintf(3, "syntax error !\n");
			return (2);
		}
		dprintf(3, "good syntax\n");
		commands = cmd(&tmp);
		expand_var(&commands, &env_var/*, exit_status*/);
		red_treatment(&commands);
		dprintf(3, "\n exit status : %d\n", cmd_last(commands)->exit_s);
		dprintf(3, "Exec:\n");
		execution(commands, env_var);
		dprintf(3, "exec over.\n\n");
		if (commands->arguments && is_builtins(commands->arguments->content))
			handle_builtins(commands);
		token_clear(tmp);
		cmd_clear(commands);
	}
    env_clear(env_var);
	return (0);
}
