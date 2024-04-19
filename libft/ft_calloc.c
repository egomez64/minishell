/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:18:49 by egomez            #+#    #+#             */
/*   Updated: 2023/11/08 16:15:32 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	tot;

	tot = nmemb * size;
	if (tot == 0)
		return (ft_calloc(1, 1));
	else if (tot / size != nmemb)
		return (NULL);
	else
	{
		ptr = malloc(tot);
		if (ptr)
			ft_bzero(ptr, tot);
	}
	return (ptr);
}
