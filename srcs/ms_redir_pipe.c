/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:17:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/11 18:15:47 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	dup_fd[2];

static bool	right_pipe_execute(t_command *command_line, int *pipefd, pid_t pid)
{
	bool	status;

	if (command_line->input == NULL)
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	status = redir_execute(command_line);
	dup2(dup_fd[0], STDIN_FILENO);
	return (status);
}

static void	left_pipe_execute(t_command *command_line, int *pipefd)
{
	if (command_line->output == NULL)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	section_execute(command_line);
	exit(EXIT_SUCCESS);
}

bool	redir_pipe(t_command *left_cmd, t_command *right_cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) != 0)
	{
		perror("pipe");
		return (false);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (false);
	}
	if (pid == 0)
		left_pipe_execute(left_cmd, pipefd);
	return (right_pipe_execute(right_cmd, pipefd, pid));
}
