/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:21:04 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 16:42:04 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include "minishell.h"

extern int dup_fd[2];

static void	hr_doc_input(char *end, int fd)
{
	int		ret;
	char	line[1024];
	size_t	n;

	while (1)
	{
		ft_putstr_fd("> ", dup_fd[1]);
		ret = read(dup_fd[0], line, 1024);
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

void	here_document(t_command *command_line, char **commamd)
{
	int	fd;

	fd = open(HERE_DOCFILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		return ;
	}
	hr_doc_input(command_line->command[0], fd);
	close(fd);
	fd = open(HERE_DOCFILE, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	redir_exec(command_line->next, commamd);
}

void	redir_inp(t_command *command_line, char **commamd)
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
	redir_exec(command_line->next, commamd);
}

void	redir_out(t_command *command_line, char **commamd)
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
	redir_exec(command_line->next, commamd);
}

void	redir_app(t_command *command_line, char **commamd)
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
	redir_exec(command_line->next, commamd);
}
