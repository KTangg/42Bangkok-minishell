/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 09:40:40 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/02 17:59:54 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getcmdlen(const char *line, int *pos)
{
	int	sq_open;
	int	dq_open;
	int	cmd_len;

	sq_open = 0;
	dq_open = 0;
	cmd_len = 0;
	while (line[*pos] && (!isredir(line[*pos]) || sq_open == 1 || dq_open == 1))
	{
		if (line[*pos] == '\'' && dq_open != 1)
			sq_open = !sq_open;
		else if (line[*pos] == '\"' && sq_open != 1)
			dq_open = !dq_open;
		(*pos)++;
		cmd_len++;
	}
	return (cmd_len);
}

// Return >0 if opening/closing quotes; 1 = single quotes; 2 = double quotes;
int	isquoting(char c, int *sq_open, int *dq_open)
{
	if (c == '\'' && !(*dq_open))
	{
		*sq_open = !(*sq_open);
		return (1);
	}
	else if (c == '\"' && !(*sq_open))
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
		if (pos == 1 && !(c >= '0' && c <= '9'))
			return (0);
	}
	return (1);
}
