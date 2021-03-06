/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:37 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/23 17:56:43 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					checkredir(const char *line, int len);
static t_command	*split_redir(t_command *cmdlist, const char *line);
static int			getredir(const char *line, int *offset);
static int			checkquote(char *line);

// Split
t_command	*parse_seqcmds(char *line)
{
	t_command	*cmdlist;
	int			len;

	if (!checkquote(line))
		return (NULL);
	len = ft_strlen(line) - 1;
	while (len >= 0)
	{
		if (!isredir(line[len]) && line[len] != ' ')
			break ;
		else if (line[len] == ' ')
			len--;
		else if (isredir(line[len]))
		{
			if (len > 0 && isredir(line[len - 1]))
				print_synterr(&line[len]);
			else
				print_synterr("newline");
			return (NULL);
		}
	}
	cmdlist = split_redir(NULL, line);
	if (!cmdlist)
		return (NULL);
	return (checkcmdlst(cmdlist));
}

static int	checkquote(char *line)
{
	t_parexcp	parexcp;

	init_parexcp(&parexcp);
	while (*line)
	{
		isquoting(*line, &parexcp);
		line++;
	}
	if (parexcp.any_open)
	{
		print_quoteerr();
		return (0);
	}
	return (1);
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
	init_cmd(cmd);
	cmd->redirection = getredir(line, &offset);
	if (cmd->redirection == -1)
		return (NULL);
	i += offset;
	cmd_len += getcmdlen(line, &i, &(cmd->recursive));
	cmd->command = split_args(line + offset, cmd_len);
	cmd->next = cmdlist;
	if (cmd->redirection == REPIPE && cmd->next == NULL)
		print_synterr("|");
	if (cmd->redirection == REPIPE && cmd->next == NULL)
		return (NULL);
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
	else
	{
		print_synterr(line);
		return (-1);
	}
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
		else if (!ft_strncmp(line, "||", len))
			return (REOR);
		print_synterr(line);
		return (-1);
	}
	return (0);
}
