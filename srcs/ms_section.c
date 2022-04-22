/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_section.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:37:14 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 12:35:18 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static t_command	*last_pipe(t_command *cmd_list)
{
	t_command	*cursor;

	cursor = cmd_list;
	while (cursor != NULL)
	{
		if (cursor->redirection != REPIPE)
			return (cursor);
		cursor = cursor->next;
	}
	return (cursor);
}

static void	add_pipe(t_command *cmd_list, t_command *last_pipe)
{
	t_command	*cursor;
	t_command	*next;

	cursor = cmd_list;
	while (cursor != last_pipe)
	{
		next = cursor->next;
		cursor->next_pipe = next;
		cursor->next = NULL;
		cursor = next;
	}
	next = cursor->next;
	cursor->next_pipe = next;
	cursor->next = NULL;
	last_pipe->next_pipe = NULL;
	cmd_list->next = next;
	cmd_list->redirection = cursor->redirection;
}

t_command	*section_command(t_command *cmd_list)
{
	t_command	*cursor;
	t_command	*next;

	cursor = cmd_list;
	next = cursor->next;
	while (cursor != NULL)
	{
		cursor->next_pipe = NULL;
		if (cursor->redirection == REPIPE)
		{
			next = last_pipe(cursor);
			add_pipe(cursor, next);
			if (next == NULL)
				return (cmd_list);
			cursor = cursor->next;
			next->next = NULL;
			continue ;
		}
		cursor = cursor->next;
	}
	return (cmd_list);
}

int	section_execute(t_command *cmd_section)
{
	int		status;

	if (cmd_section->next_pipe != NULL)
		status = redir_pipe(cmd_section->next_pipe, cmd_section);
	else if (cmd_section->recursive == 1 || !is_builtin(cmd_section->command))
		status = redir_execute(cmd_section);
	else
		status = execute_final(cmd_section);
	return (status);
}

int	section_list(t_command *cmd_section)
{
	int			status;

	status = 1;
	while (cmd_section != NULL)
	{
		if (cmd_section->redirection == REOR)
		{
			if (status != EXIT_SUCCESS)
				status = section_execute(cmd_section);
		}
		else if (cmd_section->redirection == REAND)
		{
			if (status == EXIT_SUCCESS)
				status = section_execute(cmd_section);
		}
		else
			status = section_execute(cmd_section);
		if (status == EXIT_EXIT)
			break ;
		cmd_section = cmd_section->next;
	}
	return (status);
}
