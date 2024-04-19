/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:32 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 16:59:03 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pointer_src;
	unsigned char	*pointer_dest;

	if (!dest && !src)
		return (NULL);
	i = 0;
	pointer_src = (unsigned char *)src;
	pointer_dest = dest;
	if (dest > src)
	{
		while (n-- > 0)
			pointer_dest[n] = pointer_src[n];
	}
	else
	{
		while (i < n)
		{
			pointer_dest[i] = pointer_src[i];
			i++;
		}
	}
	return (dest);
}
