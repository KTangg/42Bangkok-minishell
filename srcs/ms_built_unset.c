/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:00:04 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 22:10:30 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		rm_environ(char *index);
static t_vars	*get_prevvar(char *index, t_vars *head);

extern t_ms_vars	*g_msvars;

int	cmd_unset(char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (!check_varn(argv[i]))
			cmd_varerr(argv[0], argv[i]);
		else
			unsetvar(argv[i], 0);
		i++;
	}
	return (0);
}

// Unset var given lst parameter
// 0 - Check from both environmental and local
// 1 - Check environmental only; 2 - Check local only
void	unsetvar(char *index, int lst)
{
	t_vars	*temp;
	t_vars	*prev;

	temp = *(g_msvars->env_lst);
	if (lst == 0 || lst == 1)
		temp = get_prevvar(index, *(g_msvars->env_lst));
	if (temp && lst != 2)
		rm_environ(index);
	if ((temp == NULL && lst == 0) || lst == 2)
		temp = get_prevvar(index, *(g_msvars->var_lst));
	if (temp == NULL)
		return ;
	else if (temp == *(g_msvars->var_lst))
		*(g_msvars->var_lst) = temp->next;
	else if (temp == *(g_msvars->env_lst))
		*(g_msvars->env_lst) = temp->next;
	else
	{
		prev = temp;
		temp = temp->next;
		prev->next = temp->next;
	}
	free(temp->index);
	free(temp->value);
	free(temp);
}

static t_vars	*get_prevvar(char *index, t_vars *head)
{
	t_vars	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	if (!ft_strcmp(temp->index, index))
		return (temp);
	while (temp->next && ft_strcmp(temp->next->index, index))
		temp = temp->next;
	if (temp->next == NULL)
		return (NULL);
	if (!ft_strcmp(temp->next->index, index))
		return (temp);
	else
		return (NULL);
}

static void	rm_environ(char *index)
{
	int		i;
	t_vars	*temp;
	int		size;
	int		pos;
	char	**newenv;

	i = -1;
	pos = 0;
	size = getarrsize(g_msvars->environ);
	temp = *(g_msvars->env_lst);
	while (temp && ft_strcmp(temp->index, index) && pos++ >= 0)
		temp = temp->next;
	if (!temp)
		return ;
	newenv = (char **)malloc((size) * sizeof(char *));
	while (++i < pos)
		newenv[i] = (g_msvars->environ)[i];
	free((g_msvars->environ)[pos]);
	i--;
	while (++i < size - 1)
		newenv[i] = (g_msvars->environ)[i + 1];
	newenv[i] = NULL;
	free(g_msvars->environ);
	g_msvars->environ = newenv;
}
