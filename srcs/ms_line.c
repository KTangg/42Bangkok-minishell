/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:12:32 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/04 18:20:33 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

pid_t	g_pid = 1;
int		g_wstatus = 0;

void	free_line(t_command	**cmd_section)
{
	size_t		i;
	size_t		j;
	t_command	*tmp;
	t_command	*next;

	i = 0;
	while (cmd_section[i] != NULL)
	{
		tmp = cmd_section[i];
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
		i++;
	}
	free(cmd_section);
}

void	execute_line(t_command *command_line)
{
	size_t		i;
	t_command	**cmd_section;

	i = 0;
	cmd_section = section_cmd(command_line);
	g_wstatus = -1;
	g_pid = fork();
	if (g_pid == 0)
	{
		while (cmd_section[i] != NULL)
		{
			section_execute(cmd_section[i++]);
		}
		exit(3);
	}
	waitpid(g_pid, &g_wstatus, 0);
	free_line(cmd_section);
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
