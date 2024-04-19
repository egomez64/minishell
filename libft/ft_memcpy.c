/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:21 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 16:51:21 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pointer_src;
	unsigned char	*pointer_dest;
	size_t			i;

	pointer_src = (unsigned char *)src;
	pointer_dest = dest;
	i = 0;
	if (!pointer_src && !pointer_dest)
		return (NULL);
	while (i < n)
	{
		pointer_dest[i] = pointer_src[i];
		i++;
	}
	return (dest);
}
