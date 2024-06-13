/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:13:59 by maamine           #+#    #+#             */
/*   Updated: 2024/06/13 13:23:15 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// No PATH_MAX used.
int	pwd(int argc, char **argv, char **envp)
{
	char	*wd;
	int		err;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		err = errno;
		perror("minishell: pwd");
		return (err);
	}
	printf("%s\n", wd);
	return (0);
}
