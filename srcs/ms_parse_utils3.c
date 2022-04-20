/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:15:44 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 22:04:38 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parexcp(t_parexcp *p)
{
	p->any_open = 0;
	p->sq_open = 0;
	p->dq_open = 0;
	p->p_open = 0;
}

void	init_cmd(t_command *cmd)
{
	cmd->recursive = 0;
	cmd->redirection = 0;
	cmd->next = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
}

char	**arr_app(char **chain, char **newcmd)
{
	int		newsize;
	char	**newarr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!chain)
		newsize = getarrsize(newcmd);
	else
		newsize = getarrsize(chain) + getarrsize(newcmd);
	newarr = (char **)malloc((newsize + 1) * sizeof(char *));
	while (chain && i < getarrsize(chain))
	{
		newarr[i] = chain[i];
		i++;
	}
	free(chain[i]);
	free(chain);
	while (i < newsize)
		newarr[i++] = newcmd[j++];
	newarr[i] = NULL;
	free(newcmd[j]);
	free(newcmd);
	return (newarr);
}

char	**cmd_app(char **arr, char *str)
{
	int		i;
	int		size;
	char	**newarr;

	i = 0;
	if (!arr)
		size = 0;
	else
		size = getarrsize(arr);
	newarr = (char **)malloc((size + 2) * sizeof(char *));
	if (!newarr)
		return (NULL);
	while (arr && arr[i])
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i++] = ft_strdup(str);
	newarr[i] = NULL;
	if (arr)
		free(arr);
	return (newarr);
}

int	checkrepeat(char **arr, int size, char *str)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!ft_strcmp(arr[i], str))
			return (1);
		i++;
	}
	return (0);
}
