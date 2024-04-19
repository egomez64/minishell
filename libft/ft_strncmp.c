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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*chain1;
	unsigned char	*chain2;

	i = 0;
	chain1 = (unsigned char *)s1;
	chain2 = (unsigned char *)s2;
	if ((n == 0) || (!s1 && !s2))
		return (0);
	while (i < n)
	{
		if (chain1[i] != chain2[i] || chain1[i] == 0
			|| chain2[i] == 0)
			return (chain1[i] - chain2[i]);
		i++;
	}
	return (0);
}
