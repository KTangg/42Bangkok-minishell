/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:55:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 09:12:41 by tratanat         ###   ########.fr       */
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

void	parsevarset(char *cmd, t_vars **lst)
{
	int		i;
	char	**nvar;

	nvar = ft_split(cmd, '=');
	setvar(nvar[0], nvar[1], lst);
	i = 0;
	while (nvar[i])
		free(nvar[i++]);
	free(nvar);
}

void	setvar(char *index, char *value, t_vars **lst)
{
	t_vars	*temp;

	if (lst && *lst == NULL)
		app_var(lst, index, value);
	temp = *(g_msvars->env_lst);
	if (!lst || temp == *lst)
		while (temp && ft_strcmp(temp->index, index))
			temp = temp->next;
	if ((!lst && temp == NULL) || lst == g_msvars->var_lst)
	{
		temp = *(g_msvars->var_lst);
		while (temp && ft_strcmp(temp->index, index))
			temp = temp->next;
	}
	if (temp == NULL && !lst)
		app_var(g_msvars->var_lst, index, value);
	else if (temp == NULL && lst)
		app_var(lst, index, value);
	else
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
}

void	unsetvar(char *index)
{
	t_vars	*temp;
	t_vars	*clean;

	temp = *(g_msvars->env_lst);
	while (temp && temp->next && ft_strcmp(temp->next->index, index))
		temp = temp->next;
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
