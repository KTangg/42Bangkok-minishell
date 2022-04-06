/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 09:40:40 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 10:16:47 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

static void	lst_relist(char **oldlst, char **newlst, int pos, int size);

int	getcmdlen(const char *line, int *pos, int *recursive)
{
	int	sq_open;
	int	dq_open;
	int	cmd_len;
	int	p_open;

	sq_open = 0;
	dq_open = 0;
	cmd_len = 0;
	p_open = 0;
	*recursive = 0;
	while (line[*pos] && ((!isredir(line[*pos]) && !p_open) || sq_open || dq_open || p_open))
	{
		isquoting(line[*pos], &sq_open, &dq_open, &p_open);
		cmd_len++;
		(*pos)++;
		if (p_open)
			*recursive = 1;
	}
	if (!(line[*pos]) && p_open)
		return (-1);
	return (cmd_len);
}

// Return >0 if opening/closing quotes; 1 = single quotes; 2 = double quotes;
int	isquoting(char c, int *sq_open, int *dq_open, int *p_open)
{
	if (c == '(' && !(*sq_open) && !(*dq_open))
	{
		(*p_open)++;
		return (3);
	}
	else if ( c == ')' && !(*sq_open) && !(*dq_open))
	{
		(*p_open)--;
		return (3);
	}
	else if (c == '\'' && !(*dq_open) && !(*p_open))
	{
		*sq_open = !(*sq_open);
		return (1);
	}
	else if (c == '\"' && !(*sq_open) && !(*p_open))
	{
		*dq_open = !(*dq_open);
		return (2);
	}
	return (0);
}

int	validvarn(char c, int pos)
{
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') && !(c == '_'))
	{
		if (pos == 0)
			return (0);
		if (pos > 0 && !(c >= '0' && c <= '9'))
			return (0);
	}
	return (1);
}

char	**lst_delcmd(t_command *cmdlist, char *cmd)
{
	int			i;
	int			arr_size;
	char		**newlst;

	i = 0;
	arr_size = 0;
	while ((cmdlist->command)[arr_size])
		arr_size++;
	while (ft_strcmp(cmdlist->command[i], cmd))
		i++;
	if (!ft_strcmp(cmdlist->command[i], cmd))
	{
		newlst = (char **)malloc(arr_size * sizeof(char *));
		lst_relist(cmdlist->command, newlst, i, arr_size);
		free(cmdlist->command[i]);
		free(cmdlist->command);
		return (newlst);
	}
	return (cmdlist->command);
}

static void	lst_relist(char **oldlst, char **newlst, int pos, int size)
{
	int	i;

	i = 0;
	if (size == 1)
	{
		newlst[0] = NULL;
		return ;
	}
	while (i < pos)
	{
		newlst[i] = oldlst[i];
		i++;
	}
	pos++;
	while (oldlst[pos])
		newlst[i++] = oldlst[pos++];
	newlst[i] = '\0';
}
