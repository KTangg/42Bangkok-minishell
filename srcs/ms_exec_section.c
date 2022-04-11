/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_section.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:37:14 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/11 18:23:30 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	section_execute(t_command *cmd_section)
{
	if (cmd_section == NULL)
		return (false);
	else if (cmd_section->redirection == 0)
		return (redir_execute(cmd_section));
	else if (cmd_section->redirection == REPIPE)
		return (redir_pipe(cmd_section->next, cmd_section));
	/*else if (cmd_section->redirection == REAND)
		return (redir_and(cmd_section->next, cmd_section));
	else if (cmd_section->redirection == REOR)
		return (redir_or(cmd_section->next, cmd_section));*/
	return (false);
}
