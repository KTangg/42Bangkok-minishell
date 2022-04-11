/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:18:53 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/11 18:23:34 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_execute(t_command *command_line)
{
	if (command_line == NULL)
		return (false);
	if (command_line->recursive == 1)
		return (shell_line(command_line->command[0]));
	else
	{
		/*if (is_builtin(command_line->command))
			return (execute_builtin(command_line));
		else
			return (execute_execve(command_line));*/
		return (execute_execve(command_line->command));
	}
}
