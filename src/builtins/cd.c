/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:35:02 by maamine           #+#    #+#             */
/*   Updated: 2024/07/04 17:50:16 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_home(t_env *envi)
{
	int		ret;
	char	*home;

	while (envi && (ft_strcmp(envi->name, "HOME")))
		envi = envi->next;
	if (!envi)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	home = envi->val;
	ret = chdir(home);
	return (ret);
}

static void	error_message(char *arg, int err)
{
	char	*str;
	char	*message;
	int		path_len;
	int		message_len;

	message = strerror(err);
	if (!message)
		return ;
	path_len = ft_strlen(arg);
	message_len = ft_strlen(message);
	str = malloc((19 + path_len + message_len) * sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, "minishell: cd: ", 16);
	ft_strlcpy(str + 15, arg, path_len + 1);
	ft_strlcpy(str + 15 + path_len, ": ", 3);
	ft_strlcpy(str + 17 + path_len, message, message_len + 1);
	ft_strlcpy(str + 17 + path_len + message_len, "\n", 2);
	write(2, str, ft_strlen(str));
	free(str);
}

int	cd(t_cmd *cmd, t_env *envi)
{
	int	ret;
	int	argc;

	argc = ft_lstsize(cmd->arguments);
	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (argc == 1)
		ret = cd_home(envi);
	else
		ret = chdir((char *) cmd->arguments->next->content);
	if (ret == -1)
	{
		error_message(cmd->arguments->next->content, errno);
		return (1);
	}
	return (ret);
}
