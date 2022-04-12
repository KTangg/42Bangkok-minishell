/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:21:04 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/12 16:31:45 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

extern t_ms_vars	*g_msvars;

static void	hr_doc_input(char *end, int fd)
{
	int		ret;
	char	line[1024];
	size_t	n;

	while (1)
	{
		ft_putstr_fd("> ", g_msvars->dup_fd[1]);
		ret = read(g_msvars->dup_fd[0], line, 1024);
		if (ret == 0)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file",
				STDERR_FILENO);
			break ;
		}
		if (ret > 0)
			line[ret - 1] = '\0';
		if (ft_strcmp(line, end) == 0)
			break ;
		n = ft_strlen(line);
		write(fd, line, n);
		write(fd, "\n", 1);
	}
}

int	here_document(char *end)
{
	int	fd;

	fd = open(HERE_DOCFILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("here document");
		return (fd);
	}
	hr_doc_input(end, fd);
	close(fd);
	fd = open(HERE_DOCFILE, O_RDONLY, 0644);
	if (fd < 0)
		perror("here document");
	return (fd);
}

int	redir_inp(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
		perror(path);
	return (fd);
}

int	redir_out(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror(path);
	return (fd);
}

int	redir_app(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		perror(path);
	return (fd);
}
