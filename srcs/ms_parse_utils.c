/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:03:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/01 10:44:05 by tratanat         ###   ########.fr       */
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
	char	*temp;

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
		temp = output[arg_set];
		output[arg_set] = ft_strtrim(output[arg_set], " ");
		free(temp);
		arg_set++;
	}
	output[argc] = NULL;
	return (output);
}

static int	getargc(const char *line, int len)
{
	int	i;
	int	argc;
	int	quote_open;

	i = 0;
	argc = 0;
	quote_open = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '\"')
			quote_open = !quote_open;
		else if (line[i] == ' ' && quote_open != 1)
		{
			while (line[i + 1] == ' ')
				i++;
			argc++;
		}
		i++;
	}
	if ((i == len || !line[i]) && line[i - 1] != ' ' && i > 0)
		argc++;
	return (argc);
}

static char	*getargv(const char *line, int len, int *offset)
{
	int		quote_open;
	int		arg_len;
	int		arg_off;

	arg_len = 0;
	quote_open = 0;
	arg_off = 0;
	while (line[*offset] && *offset < len)
	{
		if (line[*offset] == '\"')
			quote_open = !quote_open;
		else if (line[*offset] == ' ' && !quote_open)
		{
			while (line[*offset] == ' ')
			{
				(*offset)++;
				arg_off--;
			}
			break ;
		}
		(*offset)++;
		if (line[*offset] != '\"')
			arg_len++;
	}
	return (skipquote(line + arg_off + *offset - arg_len, arg_len));
}

static char	*skipquote(const char *str, int len)
{
	char	*output;
	int		i;

	i = 0;
	output = (char *)malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (i < len)
	{
		if (*str != '\"')
		{
			output[i++] = *str;
		}
		str++;
	}
	output[i] = '\0';
	return (output);
}