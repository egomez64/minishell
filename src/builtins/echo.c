/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:33:14 by maamine           #+#    #+#             */
/*   Updated: 2024/06/13 14:50:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int    option_no_newline(char *s)
{
	int    i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

static size_t    lst_len(t_list *lst)
{
	size_t    len;

	if (!lst)
		return (0);
	len = ft_strlen((char *) lst->content);
	lst = lst->next;
	while (lst)
	{
		if (lst->content)
			len += ft_strlen((char *) lst->content) + 1;
		lst = lst->next;
	}
	return (len);
}

static size_t    lst_str_join(char *dest, t_list *lst, size_t len)
{
	size_t    i;

	if (!lst)
		return (0);
	i = ft_strlcpy(dest, (char *) lst->content, len + 1);
	lst = lst->next;
	while (lst)
	{
		dest[i] = ' ';
		i++;
		i += ft_strlcpy(dest + i, (char *) lst->content, len + 1);
		lst = lst->next;
	}
	return (i);
}

static char    *lst_to_str(t_list *lst, int no_newline)
{
	char    *str;
	size_t    len;
	size_t    i;

	len = lst_len(lst);
	str = malloc((len + !no_newline + 1) * sizeof (char));
	if (!str)
		return (NULL);
	i = lst_str_join(str, lst, len);
	if (!no_newline)
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int    echo(t_cmd *cmd)
{
	int        no_newline;
	t_list    *arg;
	char    *str;

	arg = cmd->arguments->next;
	if (!arg)
	{
		printf("\n");
		return (0);
	}
	no_newline = option_no_newline(arg->content);
	if (no_newline)
		arg = arg->next;
	str = lst_to_str(arg, no_newline);
	if (!str)
	{
		return (1);    //
	}
	printf("%s", str);
	free(str);
	return (0);
}
