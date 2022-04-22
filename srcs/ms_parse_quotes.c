/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:40:36 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 18:21:09 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getquotesnum(char *str);
static char	*stripquotes(char *str, int stripped);

void	strip_quote(char **cmdlist)
{
	int			stripped;
	int			i;
	char		*newcmd;

	i = 0;
	stripped = 0;
	if (!cmdlist || !*cmdlist || !(**cmdlist))
		return ;
	while (cmdlist[i])
	{
		stripped = getquotesnum(cmdlist[i]);
		if (stripped > 0)
		{
			newcmd = stripquotes(cmdlist[i], stripped);
			free(cmdlist[i]);
			cmdlist[i] = newcmd;
		}
		i++;
	}
}

char	*strip_cmd(char *cmd)
{
	int		stripped;
	char	*newcmd;

	if (!cmd)
		return (cmd);
	stripped = 0;
	stripped = getquotesnum(cmd);
	if (stripped > 0)
	{
		newcmd = stripquotes(cmd, stripped);
		free(cmd);
		return (newcmd);
	}
	return (cmd);
}

static int	getquotesnum(char *str)
{
	t_parexcp	parexcp;
	int			num;

	num = 0;
	init_parexcp(&parexcp);
	while (*str)
	{
		if (isquoting(*str, &parexcp))
			num++;
		str++;
	}
	return (num);
}

static char	*stripquotes(char *str, int stripped)
{
	t_parexcp	parexcp;
	int			i;
	char		*newstr;
	int			newlen;

	i = 0;
	init_parexcp(&parexcp);
	newlen = ft_strlen(str) - stripped;
	newstr = (char *)malloc((newlen + 1) * sizeof(char));
	while (*str)
	{
		while (isquoting(*str, &parexcp))
			str++;
		newstr[i++] = *str;
		str++;
	}
	newstr[i] = '\0';
	return (newstr);
}
