/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:12:32 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/11 18:23:29 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

pid_t	g_pid = 1;
int		g_wstatus = 0;

t_command	*reverse_command(t_command *command_line);

static void	free_cmd_list(t_command	*cmd_list)
{
	size_t		j;
	t_command	*tmp;
	t_command	*next;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		j = 0;
		while (tmp->command[j])
		{
			free(tmp->command[j]);
			j++;
		}
		free(tmp->command);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

bool	shell_line(char *line)
{
	bool		status;
	t_command	*cmd_list;

	status = false;
	cmd_list = parse_seqcmds(line);
	if (!cmd_list)
		return (status);
	if (getvar("DEBUG_MODE") && !ft_strcmp(getvar("DEBUG_MODE"), "1"))
		print_cmdlst(cmd_list);
	else
		status = section_execute(cmd_list);
	free_cmd_list(cmd_list);
	return (status);
}
