/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:17:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 14:05:39 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static int	check_input(t_command *command_line)
{
	t_command	*cursor;

	cursor = command_line;
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

	cursor = command_line;
	while (cursor != NULL && is_redirection(cursor))
	{
		if (cursor->redirection == REDIROUT || cursor->redirection == REDIRAPP)
			return 1;
		cursor = cursor->next;
	}
	return (0);
}

static void	right_section_execute(t_command *command_line, int *pipefd)
{
	if (!check_input(command_line))
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (command_line->recursive)
	{
		shell_line(command_line->command[0]);
	}
	else
	{
		if (is_redirection(command_line))
			redir_exec(command_line);
		else
			execute(command_line->command);
	}
}

static void	left_section_execute(t_command *command_line, int *pipefd)
{
	t_command	*cursor;

	cursor = command_line;
	while (cursor != NULL && !is_pipe(cursor))
		cursor = cursor->next;
	if (cursor == NULL)
		return ;
	cursor = cursor->next;
	if (!check_output(cursor))
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cursor != NULL)
		section_execute(cursor);
}

void	redir_pipe(t_command *command_line)
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
		left_section_execute(command_line, pipefd);
	else
		right_section_execute(command_line, pipefd);
}
