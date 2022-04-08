/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:00:04 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 18:29:48 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

int	cmd_unset(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		unsetvar(argv[i]);
	}
}

void	unsetvar(char *index)
{
	t_vars	*temp;
	t_vars	*clean;

	temp = *(g_msvars->env_lst);
	while (temp && temp->next && ft_strcmp(temp->next->index, index))
		temp = temp->next;
	if (!temp)
		return (-1);
	if (temp->next == NULL)
	{
		temp = *(g_msvars->var_lst);
		while (temp && temp->next && ft_strcmp(temp->next->index, index))
			temp = temp->next;
	}
	if (temp->next == NULL)
		return ;
	else
	{
		clean = temp->next;
		temp->next = temp->next->next;
		free(clean->index);
		free(clean->value);
		free(clean);
	}
}
