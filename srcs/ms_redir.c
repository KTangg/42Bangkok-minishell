/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:21:04 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/03 15:41:42 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include "minishell.h"

void	hr_doc_input(char *end, int fd)
{
	char	*line;
	size_t	n;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file",
				STDERR_FILENO);
			break ;
		}
		n = ft_strlen(line);
		if (ft_strncmp(line, end, n) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, n);
		write(fd, "\n", 1);
		free(line);
	}
}

void	here_document(t_command *command_line)
{
	int	fd;

	fd = open(HERE_DOCFILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		return ;
	}
	hr_doc_input(".", fd);
	close(fd);
	fd = open(HERE_DOCFILE, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	section_execute(command_line->next);
}

void	redir_inp(t_command *command_line)
{
	int		fd;
	char	*path;

	path = command_line->command[0];
	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(path);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	section_execute(command_line->next);
}

void	redir_out(t_command *command_line)
{
	int		fd;
	char	*path;

	path = command_line->command[0];
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(path);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	section_execute(command_line->next);
}

void	redir_app(t_command *command_line)
{
	int		fd;
	char	*path;

	path = command_line->command[0];
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(path);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	section_execute(command_line->next);
}
