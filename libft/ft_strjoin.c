/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:33:54 by egomez            #+#    #+#             */
/*   Updated: 2023/11/08 18:08:28 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		tot_size;
	char	*newchain;

	if (!s1 || !s2)
		return (NULL);
	tot_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (tot_size == 0)
		return (NULL);
	newchain = ft_calloc((size_t)tot_size, sizeof(char));
	if (newchain == NULL)
		return (NULL);
	ft_strlcat(newchain, s1, tot_size);
	ft_strlcat(newchain, s2, tot_size);
	return (newchain);
}
