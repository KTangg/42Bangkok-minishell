/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:10:11 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 21:57:59 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

static void	ms_cleanup_charlst(char **charlst);
static void	ms_cleanup_varlst(t_vars **varlst);

void	ms_cleanup_global(void)
{
	ms_cleanup_charlst(g_msvars->environ);
	ms_cleanup_varlst(g_msvars->env_lst);
	if (*(g_msvars->var_lst))
		ms_cleanup_varlst(g_msvars->var_lst);
	else
		free(g_msvars->var_lst);
	free(g_msvars);
}

static void	ms_cleanup_charlst(char **charlst)
{
	int	i;

	i = 0;
	while (charlst[i] != NULL)
		free(charlst[i++]);
	free(charlst);
}

static void	ms_cleanup_varlst(t_vars **varlst)
{
	t_vars	*temp;
	t_vars	*next;

	next = *varlst;
	while (next != NULL)
	{
		temp = next;
		next = next->next;
		free(temp->index);
		free(temp->value);
		free(temp);
	}
	free(varlst);
}

void	clean_cmdfiles(t_redirect *target)
{
	t_redirect	*temp;

	temp = target;
	while (target)
	{
		target = target->next;
		if (temp->file)
			free(temp->file);
		free(temp);
		temp = target;
	}
}
