/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcards2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:47:19 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 23:51:10 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_wild_head(t_searched **pool, char *cmd, int *offset);
void		patt_search(t_searched **pool, char *patt);
void		wild_checkend(t_searched **pool);
char		**get_searched(t_searched **pool);
t_searched	**wild_init_pool(void);
static void	get_patt_head(t_searched **pool, char *cmd, int *offset);
int			getsearchoffset(char *hay, char *needle);

char	**get_wild_patt(char *cmd)
{
	int			offset;
	char		**current;
	t_searched	**pool;

	offset = 0;
	pool = wild_init_pool();
	current = NULL;
	while (cmd[offset])
	{
		if (cmd[offset] == '*' && cmd[offset + 1])
			get_wild_head(pool, cmd, &offset);
		else if (cmd[offset] == '*' && !cmd[offset + 1])
			break ;
		else
			get_patt_head(pool, cmd, &offset);
	}
	if (!cmd[offset])
		wild_checkend(pool);
	current = get_searched(pool);
	return (current);
}

static void	get_patt_head(t_searched **pool, char *cmd, int *offset)
{
	int	i;
	int	len;
	int	j;

	len = 0;
	j = 0;
	cmd += *offset;
	while (cmd[len] && cmd[len] != '*')
		len++;
	*offset += len;
	while (j < len)
	{
		i = 0;
		while (pool[i])
		{
			if (pool[i]->viable == 1)
				if (pool[i]->str[pool[i]->searched + j] != cmd[j])
					pool[i]->viable = 0;
			pool[i]->searched++;
			i++;
		}
		j++;
	}
}

static void	get_wild_head(t_searched **pool, char *cmd, int *offset)
{
	int		i;
	int		patt_len;
	char	*patt;

	i = 0;
	patt_len = 0;
	while (*(cmd + *offset) && *(cmd + *offset) == '*')
		(*offset)++;
	cmd = cmd + *offset;
	while (cmd[patt_len] && cmd[patt_len] != '*')
		patt_len++;
	*offset += patt_len;
	patt = (char *)malloc((patt_len + 1) * sizeof(char));
	while (i < patt_len)
	{
		patt[i] = cmd[i];
		i++;
	}
	patt[i] = '\0';
	patt_search(pool, patt);
	free(patt);
}

void	patt_search(t_searched **pool, char *patt)
{
	int		i;
	char	*tofind;
	int		offset;
	int		patt_len;

	i = 0;
	patt_len = ft_strlen(patt);
	while (pool[i])
	{
		if (pool[i]->viable == 0)
		{
			i++;
			continue ;
		}
		tofind = pool[i]->str;
		tofind = tofind + pool[i]->searched;
		offset = getsearchoffset(tofind, patt);
		if (offset == -1)
			pool[i]->viable = 0;
		else
			pool[i]->searched += offset + patt_len;
		i++;
	}
}

int	getsearchoffset(char *hay, char *needle)
{
	int		hay_len;
	int		needle_len;
	int		i;
	int		j;

	i = 0;
	hay_len = ft_strlen(hay);
	needle_len = ft_strlen(needle);
	while (i + needle_len <= hay_len)
	{
		j = 0;
		if (hay[i] == needle[j])
		{
			while (j < needle_len && hay[i + j] == needle[j])
				j++;
			if (j == needle_len)
				return (i);
		}
		i++;
	}
	return (-1);
}
