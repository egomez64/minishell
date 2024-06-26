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

// static void	print_cmd(t_cmd *cmd)
// {
// 	t_list	*arg;
// 	t_token	*redir;

// 	while (cmd)
// 	{
// 		dprintf(3, "arg\n");
// 		arg = cmd->arguments;
// 		while (arg)
// 		{
// 			dprintf(3, "\t%s\n", (char *) arg->content);
// 			arg = arg->next;
// 		}
// 		dprintf(3, "redir\n");
// 		redir = cmd->redirections;
// 		while (redir)
// 		{
// 			dprintf(3, "\t%s\n", redir->val);
// 			redir = redir->next;
// 		}
// 		dprintf(3, ".\n");
// 		cmd = cmd->next;
// 	}
// }

int	main(int ac, char **av, char **ep)
{
	t_token		*tmp;
	char		*line;
	t_minishell	minishell;
	(void)		ac;
	(void)		av;

	open_debug(3);
	minishell.envi = get_env(ep);
	minishell.exit_status = 0;
	while(1)
	{
		line = readline("minishell> ");
		if (line == 0)
			return (0);
		add_history(line);
		if (!check_quotes(line))
		{
			printf("problems with quotes, a quotes should be open\n");
			continue;
		}
		tmp = lexer(line);
		if (!parsing(&tmp))
		{
			// dprintf(3, "syntax error !\n");	// ?
			write(2, "syntax error !\n", 16);	// ?
			return (2);
		}
		dprintf(3, "good syntax\n");
		minishell.commands = cmd(tmp);
		// dprintf(3, "print 1\n");
		// print_cmd(commands);
		// expand_var(&commands, &env_var/*, exit_status*/);
		expand_var(&minishell, minishell.exit_status);
		// dprintf(3, "print 2\n");
		// print_cmd(commands);
		red_treatment(&minishell);
		// dprintf(3, "print 3\n");
		// print_cmd(commands);
		//dprintf(3, "exit status : %d\n", minishell.commands->exit_s);
		minishell.exit_status = execution(&minishell);
		// if (commands->arguments && is_builtins(commands->arguments->content))
		// 	handle_builtins(commands);
		token_clear(tmp);
		//cmd_clear(minishell.commands);
	}
    env_clear(minishell.envi);
	return (0);
}
