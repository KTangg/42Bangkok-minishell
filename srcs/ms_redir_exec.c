/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:11:24 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/11 18:15:45 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_out(t_redirect *redirect)
{
	int	fd;

	fd = -1;
	while (redirect != NULL)
	{
		if (fd != -1)
			close(fd);
		if (redirect->redirect == 1)
			fd = redir_out(redirect->file);
		else if (redirect->redirect == 2)
			fd = redir_app(redirect->file);
		if (fd == -1)
			return (fd);
		redirect = redirect->next;
	}
	return (fd);
}

static int	get_fd_in(t_redirect *redirect)
{
	int	fd;

	fd = -1;
	while (redirect != NULL)
	{
		if (fd != -1)
			close(fd);
		if (redirect->redirect == 1)
			fd = redir_inp(redirect->file);
		else if (redirect->redirect == 2)
			fd = here_document(redirect->file);
		if (fd == -1)
			return (fd);
		redirect = redirect->next;
	}
	return (fd);
}

static void	init_fd(int *fd, int *fd_dup)
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd_dup[0] = dup(fd[0]);
	fd_dup[1] = dup(fd[1]);
}

static void	fd_reset(int *fd_dup)
{
	dup2(fd_dup[0], STDIN_FILENO);
	dup2(fd_dup[1], STDOUT_FILENO);
	close(fd_dup[0]);
	close(fd_dup[1]);
}

bool	redir_execute(t_command *command_line)
{
	int		fd[2];
	int		fd_dup[2];
	bool	status;

	init_fd(fd, fd_dup);
	if (command_line->output != NULL)
	{
		fd[1] = get_fd_out(command_line->output);
		if (fd[1] < 0)
			return (false);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (command_line->input != NULL)
	{
		fd[0] = get_fd_in(command_line->input);
		if (fd[0] < 0)
			return (false);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = check_execute(command_line);
	fd_reset(fd_dup);
	return (status);
}
