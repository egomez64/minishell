/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:44:25 by egomez            #+#    #+#             */
/*   Updated: 2023/11/08 16:17:00 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		size;

	size = ft_strlen(src) + 1;
	copy = ft_calloc(size, sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, src, size);
	return (copy);
}
