/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:12:32 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 11:01:25 by spoolpra         ###   ########.fr       */
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

static void	free_redir(t_redirect *redir)
{
	t_redirect	*tmp;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->file != NULL)
			free(tmp->file);
		redir = redir->next;
		free(tmp);
		tmp = redir;
	}
}

static void	free_pipe(t_command *pipe_list)
{
	t_command	*tmp;
	t_command	*next;

	tmp = pipe_list;
	while (tmp != NULL)
	{
		free_command(tmp->command);
		free_redir(tmp->input);
		free_redir(tmp->output);
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
		free_redir(tmp->input);
		free_redir(tmp->output);
		if (tmp->next_pipe != NULL)
			free_pipe(tmp->next_pipe);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

int	shell_line(char *line)
{
	int			status;
	t_command	*cmd_list;

	status = EXIT_FAILURE;
	cmd_list = parse_seqcmds(line);
	free(line);
	if (!cmd_list)
		return (status);
	if (getvar("DEBUG_MODE") && !ft_strcmp(getvar("DEBUG_MODE"), "1"))
		print_cmdlst(cmd_list);
	else
	{
		cmd_list = section_command(cmd_list);
		cmd_list = reverse_command(cmd_list);
		status = section_list(cmd_list);
		free_cmd_list(cmd_list);
	}
	return (status);
}
