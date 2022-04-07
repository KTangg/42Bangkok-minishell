/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:39:59 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 14:06:49 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_command *cmd)
{
	if (cmd->redirection >= REDIRIN && cmd->redirection <= REDIRHRE)
		return (1);
	return (0);
}

int	is_pipe(t_command *cmd)
{
	if (cmd->redirection == REPIPE)
		return (1);
	return (0);
}

int	is_logical(t_command *cmd)
{
	if (cmd->redirection >= REAND && cmd->redirection <= REOR)
		return (1);
	return (0);
}

void	redir_exec(t_command *command_line)
{
	if (command_line == NULL)
		return ;
	if (is_redirection(command_line))
	{
		if (command_line->redirection == REDIRIN)
			redir_inp(command_line);
		else if (command_line->redirection == REDIROUT)
			redir_out(command_line);
		else if (command_line->redirection == REDIRAPP)
			redir_app(command_line);
		else if (command_line->redirection == REDIRHRE)
			here_document(command_line);
	}
	else
	{
		if (command_line->recursive == 1)
			section_execute(command_line);
		else
			execute(command_line->command);
	}
}
