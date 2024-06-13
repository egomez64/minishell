 #include <minishell.h>

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
			printf("syntax error !\n");
			return (1);
		}
		printf("good syntax\n");
		tmp2 = cmd(&tmp);
		test = cmd(&tmp);
		while (test)
		{
			printf("arguments commande %d : ", i);
			while (test->arguments)
			{
				printf("%s, ", (char *)test->arguments->content);
				test->arguments = test->arguments->next;
			}
			printf("\nredirections commande %d : ", i);
			while (test->redirections)
			{
				printf("%s, ", (char *)test->redirections->val);
				test->redirections = test->redirections->next;
			}
			test = test->next;
			i++;
		}



		expand_var(&tmp2, &env_var);
		test = tmp2;
		while (test)
		{
			printf("\nexpand arguments commande %d : ", y);
			while (test->arguments)
			{
				printf("%s, ", (char *)test->arguments->content);
				test->arguments = test->arguments->next;
			}
			printf("\nexpand redirections commande %d : ", y);
			while (test->redirections)
			{
				printf("%s, ", (char *)test->redirections->val);
				test->redirections = test->redirections->next;
			}
			test = test->next;
			y++;
		}
		printf("\n");


		printf("Exec:\n");
		execution(tmp2, env_var);


		token_clear(tmp);
	}
    env_clear(env_var);
	return (0);
}
