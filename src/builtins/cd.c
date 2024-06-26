/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:02 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 15:27:43 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "../../includes/builtins.h"
// #include <unistd.h>
// #include <errno.h>
// #include <stdio.h>

static int	cd_home(t_env *envi/*, int *exit_s	*/)
{
	int		ret;
	char	*home;

	while (envi && (ft_strcmp(envi->name, "HOME")))
		envi = envi->next;
	if (!envi)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	home = envi->val;
	ret = chdir(home);
	return (ret);
}

int	cd(t_cmd *cmd, t_env *envi)
{
	int	ret;
	int	err;
	int argc;
	// char	*wd;	// 

	argc = ft_lstsize(cmd->arguments);
	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (argc == 1)
		ret = cd_home(envi);
	else
		ret = chdir((char *) cmd->arguments->next->content);
	if (ret == -1)
	{
		err = errno;
		perror("minishell: cd");
		return (err);
	}
	// // 
	// wd = getcwd(NULL, 0);
	// printf("%s", wd);
	// free(wd);
	// // 
	return (ret);
}
