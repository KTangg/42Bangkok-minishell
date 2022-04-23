/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:26:57 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/23 17:13:11 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_cmdapp(t_command *cmd, char **toapp);

t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur)
{
	t_command	*prev;
	t_command	*target;

	prev = cmdlst;
	if (cur->next == NULL)
		return (lst_nocmdfile(cur));
	target = cur->next;
	if (prev != cur)
		while (prev->next != cur)
			prev = prev->next;
	move_filecmd(cur, target);
	if (*cur->command)
	{
		lst_cmdapp(target, &(cur->command[1]));
		free(cur->command[0]);
	}
	if (prev != cur)
		prev->next = target;
	free(cur->command);
	if (cur == prev || cur == cmdlst)
	{
		free(cur);
		return (target);
	}
	return (cmdlst);
}

t_command	*lst_nocmdfile(t_command *cur)
{
	int		size;
	char	**temp;
	int		i;

	move_filecmd(cur, cur);
	size = getarrsize(cur->command);
	if (size > 1)
	{
		free(cur->command[0]);
		i = -1;
		temp = (char **)malloc(size * sizeof(char *));
		while (++i < size - 1)
			temp[i] = cur->command[i + 1];
		temp[i] = NULL;
		free(cur->command);
		cur->command = temp;
	}
	else
	{
		free(cur->command[0]);
		cur->command[0] = NULL;
	}
	return (cur);
}

static void	lst_cmdapp(t_command *cmd, char **toapp)
{
	int		arr_size;
	int		i;
	char	**newargv;

	if (!toapp || !(*toapp) || !(**toapp))
		return ;
	arr_size = getarrsize(cmd->command);
	i = 0;
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
