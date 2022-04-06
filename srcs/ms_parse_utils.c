/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:03:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 17:45:11 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**split_args(const char *line, int len);
static char	*skipquote(const char *str, int len);
static int	getargc(const char *line, int len);
static char	*getargv(const char *line, int len, int *offset);
static char	*skipquote(const char *str, int len);

char	**split_args(const char *line, int len)
{
	int		argc;
	char	**output;
	int		offset;
	int		arg_set;

	offset = 0;
	arg_set = 0;
	argc = getargc(line, len);
	output = (char **)malloc((argc + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	while (arg_set < argc)
	{
		output[arg_set] = getargv(line, len, &offset);
		if (!output[arg_set])
			return (NULL);
		arg_set++;
	}
	output[argc] = NULL;
	return (output);
}

static int	getargc(const char *line, int len)
{
	int	i;
	int	argc;
	int	sq_open;
	int	dq_open;
	int	p_open;

	i = 0;
	argc = 0;
	sq_open = 0;
	dq_open = 0;
	p_open = 0;
	while (line[i] && i < len)
	{
		if (isquoting(line[i], &sq_open, &dq_open, &p_open))
			;
		else if (line[i] == ' ' && !sq_open && !dq_open && !p_open)
		{
			while (line[i + 1] == ' ')
				i++;
			argc++;
		}
		i++;
	}
	argc += ((i == len || !line[i]) && line[i - 1] != ' ' && i > 0);
	return (argc);
}

static char	*getargv(const char *line, int len, int *offset)
{
	int	sq_open;
	int	dq_open;
	int	arg_len;
	int	arg_off;
	int	p_open;

	arg_len = 0;
	sq_open = 0;
	dq_open = 0;
	arg_off = 0;
	p_open = 0;
	while (line[*offset] && *offset < len)
	{
		if (isquoting(line[*offset], &sq_open, &dq_open, &p_open) && !p_open && !sq_open && !dq_open)
			arg_off--;
		else if (line[*offset] == ' ' && !sq_open && !dq_open && !p_open)
		{
			while (line[*offset] == ' ')
				arg_off -= !!((*offset)++);
			break ;
		}
		else if (!(p_open == 0 && line[*offset] == ')'))
			if (!(p_open == 1 && line[*offset] == '('))
				arg_len++;
		(*offset)++;
	}
	return (skipquote(line + arg_off + *offset - arg_len, arg_len));
}

static char	*skipquote(const char *str, int len)
{
	char	*output;
	int		i;
	int		sq_open;
	int		dq_open;
	int		p_open;

	i = 0;
	sq_open = 0;
	dq_open = 0;
	p_open = 0;
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (i < len)
	{
		if (isquoting(*str, &sq_open, &dq_open, &p_open))
			str++;
		if (sq_open || dq_open || p_open)
			output[i++] = *str;
		else if (*str != ' ' && !sq_open && !dq_open && !p_open)
			output[i++] = *str;
		str++;
	}
	output[i] = '\0';
	return (output);
}

int	isredir(const char c)
{
	const char	redir[4] = "><|&";
	int			i;

	i = 0;
	while (i < 4)
		if (c == redir[i++])
			return (1);
	return (0);
}
