/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:15:46 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 18:24:42 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	const char		*chain1;
	const char		*chain2;

	i = 0;
	chain1 = s1;
	chain2 = s2;
	while (i < n)
	{
		if (chain1[i] != chain2[i])
			return ((unsigned char)chain1[i] - (unsigned char)chain2[i]);
		i++;
	}
	return (0);
}
