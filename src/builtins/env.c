/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:04 by maamine           #+#    #+#             */
/*   Updated: 2024/07/04 17:48:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env(t_env *envi)
{
	while (envi)
	{
		if (envi->val)
			printf("%s=%s\n", envi->name, envi->val);
		envi = envi->next;
	}
	return (0);
}
