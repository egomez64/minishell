/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:32:38 by egomez            #+#    #+#             */
/*   Updated: 2023/11/23 15:13:17 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	new = 0;
	if (!s1)
		return (NULL);
	if (!set || set[0] == 0)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	while (s1[i] != 0 && ft_strchr(set, s1[i]))
		i++;
	while (s1[len - 1] && ft_strchr(set, s1[len - 1]) && len > i)
		len--;
	new = (ft_calloc(len - i + 1, sizeof(char)));
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s1[i], len - i + 1);
	return (new);
}
