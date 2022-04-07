/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:37:14 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/07 16:42:03 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*reverse_command(t_command *command_line)
{
	t_command	*prev;
	t_command	*next;
	t_command	*cursor;

	if (command_line == NULL)
		return (NULL);
	prev = command_line;
	cursor = command_line->next;
	prev->next = NULL;
	while (cursor != NULL)
	{
		next = cursor->next;
		cursor->next = prev;
		prev = cursor;
		cursor = next;
	}
	return (prev);
}

void	section_execute(t_command *cmd_section)
{
	t_command	*next_cmd;

	if (cmd_section == NULL)
		return ;
	next_cmd = cmd_section->next;
	while (next_cmd != NULL && is_redirection(next_cmd))
		next_cmd = next_cmd->next;
	if (next_cmd == NULL)
		redir_exec(cmd_section->next, cmd_section->command);
	else
	{
		if (is_pipe(next_cmd))
			redir_pipe(cmd_section, next_cmd);
	}
}
