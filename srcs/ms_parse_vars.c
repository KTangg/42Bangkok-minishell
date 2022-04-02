/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:15:11 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/02 18:17:50 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

static char	*getvarn(char *line, int varlen);
static char	*replacevar(char *line, int start, int oldlen, char *varname);
static char	*findvar(char *varname);
static int	getvarlen(char *line, int dq_open);

char	*expand_var(char *line)
{
	int		sq_open;
	int		dq_open;
	int		i;
	int		varlen;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	varlen = 0;
	while (line[i])
	{
		isquoting(line[i], &sq_open, &dq_open);
		if (line[i] == '$' && !sq_open && validvarn(line[i + 1], 0))
		{
			i++;
			varlen = getvarlen(line + i, dq_open);
			break ;
		}
		i++;
	}
	if (!line[i] || varlen == 0)
		return (line);
	return (expand_var(replacevar(line, i, varlen, getvarn(line + i, varlen))));
}

static int	getvarlen(char *line, int dq_open)
{
	int	i;
	int	varlen;

	i = 0;
	varlen = 0;
	while (!(line[varlen] == ' ') && line[i + varlen] && !dq_open)
	{
		if (!validvarn(line[varlen], 1))
			break ;
		varlen++;
	}
	while (!(line[varlen] == '\"') && line[i + varlen] && dq_open)
	{
		if (!validvarn(line[varlen], 1))
			break ;
		varlen++;
	}
	return (varlen);
}

static char	*replacevar(char *line, int start, int oldlen, char *varname)
{
	char	*var_value;
	int		newlen;
	char	*newline;
	int		linelen;
	int		i;

	var_value = findvar(varname);
	newlen = ft_strlen(var_value);
	linelen = ft_strlen(line) + (newlen - oldlen);
	newline = (char *)malloc((linelen + 1) * sizeof(char));
	i = -1;
	while (++i < start - 1)
		newline[i] = line[i];
	i = -1;
	while (++i < newlen)
		newline[start - 1 + i] = var_value[i];
	i = 0;
	while (line[start - 1 + oldlen + i])
	{
		newline[start - 1 + newlen + i] = line[start + oldlen + i];
		i++;
	}
	newline[start + newlen + i] = '\0';
	free(line);
	return (newline);
}

static char	*findvar(char *varname)
{
	t_vars	*temp;

	temp = *(g_msvars->env_lst);
	while (temp)
	{
		if (!ft_strncmp(temp->index, varname, ft_strlen(varname)))
			return (temp->value);
		temp = temp->next;
	}
	temp = *(g_msvars->var_lst);
	while (temp)
	{
		if (!ft_strncmp(temp->index, varname, ft_strlen(varname)))
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}

static char	*getvarn(char *line, int varlen)
{
	char	*varname;
	int		i;

	i = 0;
	varname = (char *)malloc((varlen + 1) * sizeof(char));
	while (i < varlen)
	{
		varname[i] = line[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}
