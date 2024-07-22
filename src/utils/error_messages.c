/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:06:17 by maamine           #+#    #+#             */
/*   Updated: 2024/07/22 12:06:37 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	str_error_message(char *name, char *err)
{
	char	*str;
	int		name_len;
	int		err_len;

	name_len = ft_strlen(name);
	err_len = ft_strlen(err);
	str = malloc((name_len + err_len + 15) * sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, "minishell: ", 12);
	ft_strlcpy(str + 11, name, name_len + 1);
	ft_strlcpy(str + name_len + 11, ": ", 3);
	ft_strlcpy(str + name_len + 13, err, err_len + 1);
	ft_strlcpy(str + name_len + err_len + 13, "\n", 2);
	write(2, str, name_len + err_len + 15);
	free(str);
}
