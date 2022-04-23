/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:18:53 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/23 17:22:42 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern t_ms_vars	*g_msvars;

int	recursive_exec(char *line)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAIL);
	if (pid == 0)
	{
		g_msvars->fork++;
		status = shell_line(line);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == EXIT_EXIT)
		return (EXIT_SUCCESS);
	return (WEXITSTATUS(status));
}

int	check_execute(t_command *command_line)
{
	if (command_line == NULL)
		return (EXIT_FAILURE);
	if (command_line->recursive == 1)
		return (recursive_exec(command_line->command[0]));
	else if (command_line->command[0] == NULL)
		return (EXIT_SUCCESS);
	else
	{
		if (is_builtin(command_line->command))
			return (execute_built(command_line->command));
		return (execute_execve(command_line->command));
	}
}
