/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 09:40:40 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 13:18:04 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

static void	lst_relist(char **oldlst, char **newlst, int pos, int size);

int	getcmdlen(const char *line, int *pos, int *recursive)
{
	int			cmd_len;
	t_parexcp	parexcp;

	cmd_len = 0;
	*recursive = 0;
	init_parexcp(&parexcp);
	while (line[*pos] && ((!isredir(line[*pos]) && !parexcp.p_open) \
	|| parexcp.any_open))
	{
		isquoting(line[*pos], &parexcp);
		cmd_len++;
		(*pos)++;
		if (parexcp.p_open)
			*recursive = 1;
	}
	if (!(line[*pos]) && parexcp.p_open)
		return (-1);
	return (cmd_len);
}

// Return >0 if opening/closing quotes; 1 = single quotes; 2 = double quotes;
int	isquoting(char c, t_parexcp *p)
{
	if ((c == '(' || c == ')') && !(p->sq_open) && !(p->dq_open))
	{
		if (c == '(')
			(p->p_open)++;
		else if (c == ')')
			(p->p_open)--;
		p->any_open = (p->sq_open + p->dq_open + p->p_open > 0);
		return (3);
	}
	else if (c == '\'' && !(p->dq_open) && !(p->p_open))
	{
		p->sq_open = !(p->sq_open);
		p->any_open = (p->sq_open + p->dq_open + p->p_open > 0);
		return (1);
	}
	else if (c == '\"' && !(p->sq_open) && !(p->p_open))
	{
		p->dq_open = !(p->dq_open);
		p->any_open = (p->sq_open + p->dq_open + p->p_open > 0);
		return (2);
	}
	p->any_open = (p->sq_open + p->dq_open + p->p_open > 0);
	return (0);
}

int	validvarn(char c, int pos, int set)
{
	if (set == 0 && c == '?' && pos == 0)
		return (1);
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
	newlst[i] = NULL;
}
