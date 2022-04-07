/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:03:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/07 08:27:43 by tratanat         ###   ########.fr       */
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
	int			i;
	int			argc;
	t_parexcp	parexcp;

	i = 0;
	argc = 0;
	parexcp.sq_open = 0;
	parexcp.dq_open = 0;
	parexcp.p_open = 0;
	parexcp.any_open = 0;
	while (line[i] && i < len)
	{
		if (isquoting(line[i], &parexcp))
			;
		else if (line[i] == ' ' && !parexcp.any_open)
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
	int			arg_len;
	int			arg_off;
	t_parexcp	parexcp;

	arg_len = 0;
	init_parexcp(&parexcp);
	arg_off = -(!!(*offset));
	while (line[*offset] && *offset < len)
	{
		if (isquoting(line[*offset], &parexcp))
			arg_off--;
		else if (line[*offset] == ' ' && !parexcp.any_open)
		{
			while (line[*offset] == ' ')
				arg_off -= !!((*offset)++);
			break ;
		}
		else if (!(!parexcp.any_open && isredir(line[*offset])))
			arg_len++;
		(*offset)++;
	}
	return (skipquote(line + arg_off + *offset - arg_len, arg_len));
}

static char	*skipquote(const char *str, int len)
{
	char		*output;
	int			i;
	t_parexcp	parexcp;

	i = 0;
	init_parexcp(&parexcp);
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (i < len && *str)
	{
		if (isquoting(*str, &parexcp))
			str++;
		if (parexcp.any_open)
			output[i++] = *str;
		else if (*str != ' ' && !parexcp.any_open)
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
