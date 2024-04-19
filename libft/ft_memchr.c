/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:38:10 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 18:00:05 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*chain;
	size_t			i;

	if (c > 255)
		c = c % 256;
	chain = (char *)s;
	i = 0;
	while (i < n)
	{
		if (chain[i] == c)
			return (&chain[i]);
		i++;
	}
	return (NULL);
}
