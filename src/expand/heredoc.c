/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:24:17 by egomez            #+#    #+#             */
/*   Updated: 2024/06/26 19:28:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	randomizer(char *str)
{
	int			fd;
	int			i;
	const char	table[] = "\
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

	fd = open("/dev/random", O_RDONLY);
	read(fd, str, 12);
	i = 0;
	while (i < 12)
	{
		str[i] = table[str[i] % (sizeof(table) - 1)];
		i++;
	}
}

static void	fill_file(int fd, char *s)
{
	char	*line;

	printf("\n");
	line = readline("heredoc>");
	if (line < 0)
		return ;
	while (ft_strcmp(line, s))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("heredoc> ");
	}
}

void	handle_heredoc(char *s, int *fd, int *exit_s)
{
	char	name[13];
	char	*path;

	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	randomizer(name);
	name [12] = 0;
	path = ft_strjoin("/tmp/", name);
	*fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (*fd < 0)
		return ;
	fill_file(*fd, s);
	close(*fd);
	*fd = open(path, O_RDONLY, 0666);
	if (*fd < 0)
		*exit_s = 1;
	unlink(path);
	path = NULL;
	free(path);
}
