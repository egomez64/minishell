/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:02 by maamine           #+#    #+#             */
/*   Updated: 2024/06/13 13:24:43 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

static int	cd_home(t_env *env, int *exit_s	)
{
	int		ret;
	char	*home;

	while (env && (ft_strcmp(env->name, "$HOME")))
		env = env->next;
	if (!env)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	home = env->val;
	ret = chdir(home);
	return (ret);
}

int	cd(int argc, char **argv, char **envp)
{
	int ret;
	int	err;

	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (argc == 1)
		ret = cd_home(envp);
	else
		ret = chdir(argv[1]);
	if (ret == -1)
	{
		err = errno;
		perror("minishell: cd");
		return (err);
	}
	return (ret);
}
