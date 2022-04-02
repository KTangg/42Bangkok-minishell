/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:37 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/02 10:09:22 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					checkredir(const char *line, int len);
static t_command	*split_redir(t_command *cmdlist, const char *line);
static int			getredir(const char *line, int *offset);

// Split
t_command	*parse_seqcmds(const char *line)
{
	t_command	*cmdlist;

	cmdlist = split_redir(NULL, line);
	if (!cmdlist)
		return (NULL);
	return (cmdlist);
}

static t_command	*split_redir(t_command *cmdlist, const char *line)
{
	int			i;
	int			offset;
	t_command	*cmd;
	int			cmd_len;

	if (!line || *line == '\0')
		return (cmdlist);
	i = 0;
	cmd_len = 0;
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redirection = getredir(line, &offset);
	i += offset;
	cmd_len += getcmdlen(line, &i);
	cmd->command = split_args(line + offset, cmd_len);
	if (!cmdlist)
		cmd->next = NULL;
	else
		cmd->next = cmdlist;
	return (split_redir(cmd, line + i));
}

static int	getredir(const char *line, int *offset)
{
	int	i;

	i = 0;
	*offset = i;
	if (!isredir(line[i]))
	{
		while (line[*offset] == ' ')
			(*offset)++;
		return (0);
	}
	while (isredir(line[i]))
		i++;
	if (i <= 2)
	{
		*offset = i;
		while (line[*offset] == ' ')
			(*offset)++;
		return (checkredir(line, i));
	}
	// else
		// TODO: print out redirection syntax error
	return (0);
}

int	checkredir(const char *line, int len)
{
	if (len == 1)
	{
		if (!ft_strncmp(line, "<", len))
			return (REDIRIN);
		else if (!ft_strncmp(line, ">", len))
			return (REDIROUT);
		else if (!ft_strncmp(line, "|", len))
			return (REPIPE);
	}
	else if (len == 2)
	{
		if (!ft_strncmp(line, ">>", len))
			return (REDIRAPP);
		else if (!ft_strncmp(line, "<<", len))
			return (REDIRHRE);
		else if (!ft_strncmp(line, "&&", len))
			return (REAND);
		// TODO: Change to properly print out error
		else
			printf("minishell: syntax error near unexpected token `%c\'\n", line[1]);
	}
	return (0);
}
