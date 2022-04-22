/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:17:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 12:35:16 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern t_ms_vars	*g_msvars;

static int	right_pipe_execute(t_command *command_line, int *pipefd, pid_t pid)
{
	int	status;

	if (command_line->input == NULL)
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	status = redir_execute(command_line);
	dup2(g_msvars->dup_fd[0], STDIN_FILENO);
	if (status == EXIT_EXIT)
		status = EXIT_SUCCESS;
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

static int	pipe_execute(t_command *left_cmd, t_command *right_cmd)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) != 0)
	{
		perror("pipe");
		return (PIPE_FAIL);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (FORK_FAIL);
	}
	if (pid == 0)
	{
		g_msvars->fork++;
		left_pipe_execute(left_cmd, pipefd);
	}
	return (right_pipe_execute(right_cmd, pipefd, pid));
}

int	redir_pipe(t_command *left_cmd, t_command *right_cmd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (FORK_FAIL);
	}
	if (pid == 0)
	{
		g_msvars->fork++;
		status = pipe_execute(left_cmd, right_cmd);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == EXIT_EXIT)
		return (EXIT_SUCCESS);
	return (WEXITSTATUS(status));
}
