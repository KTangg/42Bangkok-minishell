/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:46:16 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 08:48:25 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			valvarset(t_command *cmd, int ncmd);

t_command	*checkcmdlst(t_command *cmdlist)
{
	t_command	*cur;
	int			i;
	char		*tmpcmd;

	cur = cmdlist;
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
	return (cmdlist);
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
