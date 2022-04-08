/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:12:32 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/08 18:21:32 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

pid_t	g_pid = 1;
int		g_wstatus = 0;
extern t_ms_vars	*g_msvars;

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

void	execute_line(t_command *cmd_list)
{
	g_wstatus = -1;
	cmd_list = reverse_command(cmd_list);
	if (check_built(cmd_list->command, g_msvars->environ) > 0)
	{
		g_pid = fork();
		if (g_pid == 0)
		{
			section_execute(cmd_list);
			exit(3);
		}
		wait(&g_wstatus);
	}
	free_cmd_list(cmd_list);
}

int	shell_line(char *line)
{
	t_command	*cmdlist;

	cmdlist = parse_seqcmds(line);
	if (!cmdlist)
		return (-1);
	if (getvar("DEBUG_MODE") && !ft_strcmp(getvar("DEBUG_MODE"), "1"))
		print_cmdlst(cmdlist);
	else
		execute_line(cmdlist);
	return (0);
}
