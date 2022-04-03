/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:55:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/03 10:58:37 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

int	isvarset(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || *cmd == '\0')
		return (0);
	while (cmd[i])
	{
		if (i > 0 && cmd[i] == '=')
			return (1);
		if (!validvarn(cmd[i], i))
			return (0);
		i++;
	}
	return (0);
}

void	setvar(char *cmd)
{
	int		i;
	t_vars	*temp;
	char	**nvar;

	temp = *(g_msvars->env_lst);
	nvar = ft_split(cmd, '=');
	while (temp && ft_strcmp(temp->index, nvar[0]))
		temp = temp->next;
	if (temp == NULL)
	{
		temp = *(g_msvars->var_lst);
		while (temp && ft_strcmp(temp->index, nvar[0]))
			temp = temp->next;
	}
	if (temp == NULL)
		app_var(g_msvars->var_lst, cmd);
	else
	{
		free(temp->value);
		temp->value = ft_strdup(nvar[1]);
	}
	i = 0;
	while (nvar[i])
		free(nvar[i++]);
	free(nvar);
}
