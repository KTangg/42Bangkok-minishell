/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:39:59 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 16:42:06 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_command *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd->redirection >= REDIRIN && cmd->redirection <= REDIRHRE)
		return (1);
	return (0);
}

int	is_pipe(t_command *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd->redirection == REPIPE)
		return (1);
	return (0);
}

int	is_logical(t_command *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd->redirection >= REAND && cmd->redirection <= REOR)
		return (1);
	return (0);
}

void	redir_exec(t_command *command_line, char **command)
{
	if (command_line == NULL)
		execute(command);
	if (is_redirection(command_line))
	{
		if (command_line->redirection == REDIRIN)
			redir_inp(command_line, command);
		else if (command_line->redirection == REDIROUT)
			redir_out(command_line, command);
		else if (command_line->redirection == REDIRAPP)
			redir_app(command_line, command);
		else if (command_line->redirection == REDIRHRE)
			here_document(command_line, command);
	}
	else
	{
		execute(command);
	}
}
