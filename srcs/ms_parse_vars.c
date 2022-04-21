/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:15:11 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 08:56:50 by tratanat         ###   ########.fr       */
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
	t_parexcp	p;
	int			i;
	int			varlen;
	char		*varn;
	char		*output;

	init_parexcp(&p);
	i = 0;
	varlen = 0;
	while (line[i])
	{
		isquoting(line[i], &p);
		if (line[i] == '$' && !p.sq_open && validvarn(line[i + 1], 0, 0))
		{
			varlen = getvarlen(line + (++i), p.dq_open);
			break ;
		}
		i++;
	}
	if (!line[i] || varlen == 0)
		return (line);
	varn = getvarn(line + i, varlen);
	output = expand_var(replacevar(line, i, varlen, varn));
	free(varn);
	return (output);
}

static int	getvarlen(char *line, int dq_open)
{
	int	varlen;

	varlen = 0;
	if (line[0] == '?')
		return (1);
	while (!(line[varlen] == ' ') && line[varlen] && !dq_open)
	{
		if (!validvarn(line[varlen], 1, 0))
			break ;
		varlen++;
		if (varlen == 1 && line[0] == '?')
			break ;
	}
	if (dq_open)
	{
		while (!(line[varlen] == '\"' || line[varlen] == ' ') && line[varlen])
		{
			if (!validvarn(line[varlen], 1, 0))
				break ;
			varlen++;
		}
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
	newline = (char *)malloc((linelen + 2) * sizeof(char));
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
		if (!ft_strcmp(temp->index, varname))
			return (temp->value);
		temp = temp->next;
	}
	temp = *(g_msvars->var_lst);
	while (temp)
	{
		if (!ft_strcmp(temp->index, varname))
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}

static char	*getvarn(char *line, int varlen)
{
	char	*varname;
	int		i;

	if (varlen == 1 && *line == '?')
		setvar("?", ft_itoa(g_msvars->exit_status), g_msvars->var_lst);
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
