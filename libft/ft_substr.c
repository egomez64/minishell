/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:22:27 by egomez            #+#    #+#             */
/*   Updated: 2023/11/08 17:29:56 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > (size_t)ft_strlen(&s[start]))
		len = (size_t)ft_strlen(&s[start]);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (start < (size_t)ft_strlen(s) && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	return (new);
}
