/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:13:59 by maamine           #+#    #+#             */
/*   Updated: 2024/07/04 17:48:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd(void)
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
	free(wd);
	return (0);
}
