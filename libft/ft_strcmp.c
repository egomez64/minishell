/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:45 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 17:25:08 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int				i;
	unsigned char	*chain1;
	unsigned char	*chain2;

	i = 0;
	chain1 = (unsigned char *)s1;
	chain2 = (unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (chain1[i] != chain2[i])
			return (chain1[i] - chain2[i]);
		i++;
	}
	return (chain1[i] - chain2[i]);
}