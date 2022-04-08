/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:46:16 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 20:35:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			valvarset(t_command *cmd, int ncmd);
static t_command	*lst_checkfile(t_command *cmdlist);

t_command	*checkcmdlst(t_command *cmdlist)
{
	t_command	*cur;
	int			i;
	char		*tmpcmd;
	t_command	*newlist;

	newlist = lst_checkfile(cmdlist);
	cur = newlist;
	while (cur)
	{
		i = 0;
		valvarset(cur, (cur->next == NULL));
		while ((cur->command)[i])
		{
			tmpcmd = cur->command[i];
			cur->command[i] = expand_var(ft_strdup(cur->command[i]));
			free(tmpcmd);
			i++;
		}
		cur = cur->next;
	}
	return (newlist);
}

static void	valvarset(t_command *cmd, int firstcmd)
{
	if (isvarset(cmd->command[0]))
	{
		if (firstcmd == 1)
			parsevarset(cmd->command[0], NULL);
		cmd->command = lst_delcmd(cmd, cmd->command[0]);
	}
}

static t_command	*lst_checkfile(t_command *cmdlist)
{
	t_command	*cur;
	t_command	*newlist;
	t_command	*next;

	cur = cmdlist;
	if (cur)
		next = cur;
	newlist = cmdlist;
	while (next != NULL)
	{
		next = next->next;
		if (cur->redirection >= 1 && cur->redirection <= 4)
			newlist = lst_cmdfile(newlist, cur);
		cur = next;
	}
	return (newlist);
}
