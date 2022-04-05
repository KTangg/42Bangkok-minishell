/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:10:11 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/05 09:20:55 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	g_msvars;

void	ms_cleanup_global(void)
{
	ms_cleanup_charlst(g_msvars.environ);
	ms_cleanup_varlst(g_msvars.env_lst);
	ms_cleanup_varlst(g_msvars.var_lst);
}

void	ms_cleanup_charlst(char **charlst)
{
	int	i;

	i = 0;
	while (charlst[i])
		free(charlst[i++]);
	free(charlst);
}

void	ms_cleanup_varlst(t_vars **varlst)
{
	t_vars	*temp;

	temp = *varlst;
	while (*varlst)
	{
		temp = *varlst;
		*varlst = (*varlst)->next;
		free(temp->index);
		free(temp->value);
		free(temp);
	}
	free(varlst);
}
