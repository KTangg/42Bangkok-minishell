/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:11:24 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 11:04:59 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern t_ms_vars	*g_msvars;

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

int	redir_command(t_command *command_line)
{
	int	fd[2];

	if (command_line->input != NULL)
	{
		fd[0] = get_fd_in(command_line->input);
		if (fd[0] < 0)
			return (FILE_FAIL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (command_line->output != NULL)
	{
		fd[1] = get_fd_out(command_line->output);
		if (fd[1] < 0)
			return (FILE_FAIL);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (check_execute(command_line));
}

int	redir_execute(t_command *command_line)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	if (!ft_strcmp(command_line->command[0], "cd"))
		if (pipe(pipefd) == -1)
			return (PIPE_FAIL);
	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	if (pid == 0)
	{
		g_msvars->fork++;
		status = redir_command(command_line);
		if (!ft_strcmp(command_line->command[0], "cd"))
			sent_directory(pipefd);
		exit(status);
	}
	if (!ft_strcmp(command_line->command[0], "cd"))
		set_directory(pipefd);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_final(t_command *command_line)
{
	int		status;

	if (command_line == NULL)
		return (EXIT_FAILURE);
	if (*command_line->command == NULL)
		return (EXIT_SUCCESS);
	status = redir_command(command_line);
	return (status);
}
