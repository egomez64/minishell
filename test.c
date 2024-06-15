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
	t_cmd *test;
	t_token *tmp;
	char    *line;
	int     i;
	int		y;
	t_cmd	*tmp2;
	t_env	*env_var;
	(void)ac;
	(void)av;

	if (open_debug(3) == -1)
	{
		dprintf(2, "Debug error\n");
		return (1);
	}
	i = 1;
	y = 1;
	env_var = get_env(ep);
	while(1)
	{
		line = readline( "minishell>");
		if (line == 0)
			return (0);
		add_history(line);
		tmp = lexer(line);
		if (!parsing(&tmp))
		{
			dprintf(3, "syntax error !\n");
			return (1);
		}
		dprintf(3, "good syntax\n");
		tmp2 = cmd(&tmp);
		test = cmd(&tmp);
		while (test)
		{
			dprintf(3, "arguments commande %d : ", i);
			while (test->arguments)
			{
				dprintf(3, "%s, ", (char *)test->arguments->content);
				test->arguments = test->arguments->next;
			}
			dprintf(3, "\nredirections commande %d : ", i);
			while (test->redirections)
			{
				dprintf(3, "%s, ", (char *)test->redirections->val);
				test->redirections = test->redirections->next;
			}
			test = test->next;
			i++;
		}



		expand_var(&tmp2, &env_var);
		test = tmp2;
		while (test)
		{
			dprintf(3, "\nexpand arguments commande %d : ", y);
			while (test->arguments)
			{
				dprintf(3, "%s, ", (char *)test->arguments->content);
				test->arguments = test->arguments->next;
			}
			dprintf(3, "\nexpand redirections commande %d : ", y);
			while (test->redirections)
			{
				dprintf(3, "%s, ", (char *)test->redirections->val);
				test->redirections = test->redirections->next;
			}
			test = test->next;
			y++;
		}
		dprintf(3, "\n");


		dprintf(3, "Exec:\n");
		execution(tmp2, env_var);


		token_clear(tmp);
	}
    env_clear(env_var);
	return (0);
}
