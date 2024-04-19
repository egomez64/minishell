/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:46 by egomez            #+#    #+#             */
/*   Updated: 2023/11/06 17:02:29 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int value, size_t count)
{
	size_t			i;
	unsigned char	*pointer;

	pointer = s;
	i = 0;
	while (i < count)
		pointer[i++] = (unsigned char)value;
	return (s);
}
