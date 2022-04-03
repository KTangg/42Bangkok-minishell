/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_section.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:37:14 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/03 15:14:33 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_pipe(t_command *command_line);

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

t_command	*command_add_back(t_command *node, t_command *start)
{
	t_command	*cursor;

	cursor = start;
	node->next = NULL;
	if (start == NULL)
		return (node);
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = node;
	return (start);
}

void	init_section(t_command **cmd_section)
{
	int	i;

	i = 0;
	while (i < 1024)
		cmd_section[i++] = NULL;
}

t_command	**section_cmd(t_command *command_line)
{
	int			i;
	t_command	*cursor;
	t_command	*next;
	t_command	**cmd_section;

	cmd_section = (t_command **)malloc(sizeof(t_command *) * 1024);
	init_section(cmd_section);
	i = 0;
	cursor = command_line;
	while (cursor != NULL)
	{
		next = cursor->next;
		if (next == NULL)
		{
			cmd_section[i] = command_add_back(cursor, cmd_section[i]);
			break ;
		}
		cmd_section[i] = command_add_back(cursor, cmd_section[i]);
		if ((next->redirection >= 1 && next->redirection <= 4 ) &&
			cursor->redirection == 5)
			i++;
		cursor = next;
	}
	return (cmd_section);
}

void	section_execute(t_command *cmd_section)
{
	if (cmd_section != NULL)
	{
		if (cmd_section->redirection == REDIRIN)
			redir_inp(cmd_section);
		else if (cmd_section->redirection == REDIROUT)
			redir_out(cmd_section);
		else if (cmd_section->redirection == REDIRAPP)
			redir_app(cmd_section);
		else if (cmd_section->redirection == REDIRHRE)
			here_document(cmd_section);
		else if (cmd_section->redirection == REPIPE)
			redir_pipe(cmd_section);
		else if (cmd_section->redirection == 0)
			execute(cmd_section->command);
	}
}
