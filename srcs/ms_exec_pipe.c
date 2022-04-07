/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:17:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 16:42:05 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	dup_fd[2];

static int	check_input(t_command *command_line)
{
	t_command	*cursor;

	if (command_line == NULL)
		return (0);
	cursor = command_line->next;
	while (cursor != NULL && is_redirection(cursor))
	{
		if (cursor->redirection == REDIRIN || cursor->redirection == REDIRHRE)
			return 1;
		cursor = cursor->next;
	}
	return (0);
}

static int	check_output(t_command *command_line)
{
	t_command	*cursor;

	if (command_line == NULL)
		return (0);
	cursor = command_line->next;
	while (cursor != NULL && is_redirection(cursor))
	{
		if (cursor->redirection == REDIROUT || cursor->redirection == REDIRAPP)
			return 1;
		cursor = cursor->next;
	}
	return (0);
}

static void	right_pipe_execute(t_command *command_line, int *pipefd, pid_t pid)
{
	t_command	*cursor;

	cursor = command_line;
	if (cursor == NULL)
		return ;
	cursor = cursor->next;
	while (cursor != NULL && is_redirection(cursor))
		cursor = cursor->next;
	if (!check_input(cursor))
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	if (cursor == NULL)
	{
		if (command_line->recursive)
			shell_line(command_line->command[0]);
		else
			redir_exec(command_line->next, command_line->command);
	}
	else
	{
		section_execute(cursor);
	}
}

static void	left_pipe_execute(t_command *command_line, int *pipefd)
{
	if (!check_output(command_line))
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (command_line->recursive)
		shell_line(command_line->command[0]);
	else
		redir_exec(command_line->next, command_line->command);
}

void	redir_pipe(t_command *left_cmd, t_command *right_cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) != 0)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		left_pipe_execute(left_cmd, pipefd);
	else
		right_pipe_execute(right_cmd, pipefd, pid);
}
