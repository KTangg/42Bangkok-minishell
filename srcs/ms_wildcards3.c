/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcards3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:50:18 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 23:51:51 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_searched(t_searched **pool)
{
	char	**output;
	int		i;

	i = 0;
	output = NULL;
	while (pool[i])
	{
		if (pool[i]->viable == 1)
			output = cmd_app(output, pool[i]->str);
		free(pool[i]->str);
		free(pool[i]);
		i++;
	}
	free(pool);
	return (output);
}

t_searched	**wild_init_pool(void)
{
	char		**allwild;
	int			size;
	t_searched	**pool;
	int			i;

	i = 0;
	allwild = get_wild_any();
	size = getarrsize(allwild);
	pool = (t_searched **)malloc((size + 1) * sizeof(t_searched *));
	while (i < size)
	{
		pool[i] = (t_searched *)malloc(sizeof(t_searched));
		pool[i]->str = allwild[i];
		pool[i]->searched = 0;
		pool[i]->viable = 1;
		i++;
	}
	free(allwild);
	pool[i] = NULL;
	return (pool);
}

void	wild_checkend(t_searched **pool)
{
	int	i;

	i = 0;
	while (pool[i])
	{
		if (*(pool[i]->str + pool[i]->searched) != '\0')
			pool[i]->viable = 0;
		i++;
	}
}
