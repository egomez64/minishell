/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:02 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 18:09:06 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "../../includes/builtins.h"
// #include <unistd.h>
// #include <errno.h>
// #include <stdio.h>

static int	cd_home(t_env *env)
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

int	cd(t_cmd *cmd, t_env *env)
{
	int ret;
	int	err;
	int	argc;

	argc = ft_lstsize(cmd->arguments);
	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (argc == 1)
		ret = cd_home(env);
	else
		ret = chdir((char *) cmd->arguments->content);
	if (ret == -1)
	{
		err = errno;
		perror("minishell: cd");
		return (err);
	}
	return (ret);
}
