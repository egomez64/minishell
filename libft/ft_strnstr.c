/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:58:28 by egomez            #+#    #+#             */
/*   Updated: 2023/11/20 17:04:01 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*stock;

	i = 0;
	stock = (char *)big;
	n_len = ft_strlen(little);
	if (n_len == 0 || big == little || (big == NULL && len == 0))
		return (stock);
	while (stock[i] != '\0' && i < len)
	{
		c = 0;
		while (stock[i + c] != '\0' && little[c] != '\0'
			&& stock[i + c] == little[c] && i + c < len)
			c++;
		if (c == n_len)
			return (stock + i);
		i++;
	}
	return (0);
}
