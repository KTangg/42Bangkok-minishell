/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:12:32 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 08:35:37 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

extern t_ms_vars	*g_msvars;

static void	free_command(char **command)
{
	size_t	i;

	i = 0;
	while (command[i] != NULL)
		free(command[i++]);
	free(command);
}

static void	free_pipe(t_command *pipe_list)
{
	t_command	*tmp;
	t_command	*next;

	tmp = pipe_list;
	while (tmp != NULL)
	{
		free_command(tmp->command);
		next = tmp->next_pipe;
		free(tmp);
		tmp = next;
	}
}

static void	free_cmd_list(t_command	*cmd_list)
{
	t_command	*tmp;
	t_command	*next;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		free_command(tmp->command);
		if (tmp->next_pipe != NULL)
			free_pipe(tmp->next_pipe);
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
	free(line);
	if (!cmd_list)
		return (status);
	if (getvar("DEBUG_MODE") && !ft_strcmp(getvar("DEBUG_MODE"), "1"))
		print_cmdlst(cmd_list);
	else
	{
		status = section_list(cmd_list);
		free_cmd_list(cmd_list);
	}
	return (status);
}
