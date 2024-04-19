/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:07:32 by egomez            #+#    #+#             */
/*   Updated: 2023/11/20 13:58:17 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int n)
{
	int	size;

	size = 0;
	if (n == 0 || n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	alloc(int n, char **result, int size)
{
	if (n == -2147483647 - 1)
	{
		*result = ft_strdup("-2147483648");
		return (1);
	}
	*result = ft_calloc(size + 1, sizeof(char));
	return (0);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		i;

	i = 0;
	size = num_size(n);
	if (alloc(n, &result, size) == 1)
		return (result);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		result[i] = '-';
		i++;
	}
	while (size > i)
	{
		size--;
		result[size] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
