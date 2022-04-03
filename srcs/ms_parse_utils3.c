/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:15:44 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/03 12:18:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_cmdapp(t_command *cmd, char **toapp);

t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur)
{
	t_command	*prev;
	t_command	*target;

	prev = cmdlst;
	target = cur->next;
	if (prev != cur)
		while (prev->next != cur)
			prev = prev->next;
	target->fileout = ft_strdup(cur->command[0]);
	lst_cmdapp(target, &(cur->command[1]));
	if (cur->redirection == 2 && target)
		target->outmode = 1;
	else if (cur->redirection == 3 && target)
		target->outmode = 2;
	free(cur->command[0]);
	if (prev != cur)
		prev->next = target;
	free(cur->command);
	if (cur == prev)
		return (target);
	return (cmdlst);
}

static void	lst_cmdapp(t_command *cmd, char **toapp)
{
	int		arr_size;
	int		i;
	char	**newargv;

	arr_size = 0;
	i = 0;
	while (cmd->command[arr_size])
		arr_size++;
	while (toapp[i])
		i++;
	newargv = (char **)malloc((arr_size + i + 1) * sizeof(char *));
	arr_size = 0;
	while (cmd->command[arr_size])
	{
		newargv[arr_size] = cmd->command[arr_size];
		arr_size++;
	}
	free(cmd->command[arr_size]);
	i = 0;
	while (toapp[i])
		newargv[arr_size++] = toapp[i++];
	newargv[arr_size] = toapp[i];
	free(cmd->command);
	cmd->command = newargv;
}
