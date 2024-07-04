/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:24:17 by egomez            #+#    #+#             */
/*   Updated: 2024/07/03 19:21:18 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
extern int	g_sig;

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

static void	heredoc_warning(int n, char *delim)
{
	char	*str;
	char	*nptr;
	int		n_len;
	int		delim_len;

	nptr = ft_itoa(n);
	if (!nptr)
		return ;
	n_len = ft_strlen(nptr);
	delim_len = ft_strlen(delim);
	str = malloc((84 + n_len + delim_len) * sizeof (char));
	if (!str)
	{
		free (nptr);
		return ;
	}
	ft_strlcpy(str, "minishell: warning: here-document at line ", 43);
	ft_strlcpy(str + 42, nptr, n_len + 1);
	ft_strlcpy(str + 42 + n_len, " delimited by end-of-file (wanted `", 36);
	ft_strlcpy(str + 77 + n_len, delim, delim_len + 1);
	ft_strlcpy(str + 77 + n_len + delim_len, "')\n", 4);
	write(2, str, ft_strlen(str));
	free(str);
	free(nptr);
}

static int	fill_file(int fd, char *delim, int n_line)
{
	char	*line;

	signal(SIGINT, &heredoc_c);
	line = readline("heredoc> ");
	// if (!line)
	// 	return (1);
	while (ft_strcmp(line, delim))
	{
		if (g_sig == SIGINT)
		{
			free(line);
			return (130);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("heredoc> ");
	}
	if (!line)
	{
		heredoc_warning(n_line, delim);
		return (0);
	}
	return (0);
}

void	handle_heredoc(char *s, int *fd, int *exit_s, int n_line)
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
	*exit_s = fill_file(*fd, s, n_line);
	if (*exit_s)
		return ;
	close(*fd);
	*fd = open(path, O_RDONLY, 0666);
	if (*fd < 0)
		*exit_s = 1;
	unlink(path);
	free(path);
	signal(SIGINT, SIG_IGN);
}
