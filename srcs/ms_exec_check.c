/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:18:53 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/12 16:37:43 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern t_ms_vars	*g_msvars;

bool	recursive_exec(char *line)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		g_msvars->fork++;
		status = shell_line(line);
		if (status == false)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (status == 0)
		return (true);
	return (false);
}

bool	check_execute(t_command *command_line)
{
	if (command_line == NULL)
		return (false);
	if (command_line->recursive == 1)
		return (recursive_exec(command_line->command[0]));
	else
	{
		/*if (is_builtin(command_line->command))
			return (execute_builtin(command_line));
		else
			return (execute_execve(command_line));*/
		return (execute_execve(command_line->command));
	}
}
