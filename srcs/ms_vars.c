/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:35:42 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/06 17:45:20 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getarrsize(char **arr);

extern t_ms_vars	*g_msvars;

t_ms_vars	*init_global(char **envp)
{
	int			i;
	t_ms_vars	*ms_global;
	int			var_len;
	int			arr_size;

	i = 0;
	ms_global = (t_ms_vars *)malloc(sizeof(t_ms_vars));
	g_msvars = ms_global;
	ms_global->exit_status = 0;
	arr_size = getarrsize(envp);
	ms_global->environ = (char **)malloc((arr_size + 1) * sizeof(char *));
	ms_global->env_lst = (t_vars **)malloc(sizeof(t_vars *));
	*(ms_global->env_lst) = NULL;
	ms_global->var_lst = (t_vars **)malloc(sizeof(t_vars *));
	*(ms_global->var_lst) = NULL;
	while (envp[i])
	{
		var_len = ft_strlen(envp[i]);
		(ms_global->environ)[i] = (char *)malloc((var_len + 1) * sizeof(char));
		(ms_global->environ)[i] = ft_strdup(envp[i]);
		(ms_global->environ)[i][var_len] = '\0';
		parsevarset(ms_global->environ[i++], ms_global->env_lst);
	}
	(ms_global->environ)[i] = NULL;
	return (ms_global);
}

void	app_var(t_vars **lst, char *index, char *value)
{
	t_vars	*newvar;
	t_vars	*temp;

	newvar = (t_vars *)malloc(sizeof(t_vars));
	newvar->index = ft_strdup(index);
	if (value)
		newvar->value = ft_strdup(value);
	newvar->next = NULL;
	if (*lst == NULL)
		*lst = newvar;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newvar;
	}
}

void	print_varlist(t_vars **lst)
{
	t_vars	*temp;

	temp = *lst;
	while (temp)
	{
		printf("[%s] : [%s]\n", temp->index, temp->value);
		temp = temp->next;
	}
}

static int	getarrsize(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	*getvar(char *index)
{
	t_vars	*temp;

	temp = *(g_msvars->env_lst);
	while (temp)
	{
		if (!ft_strcmp(temp->index, index))
			return (temp->value);
		temp = temp->next;
	}
	temp = *(g_msvars->var_lst);
	while (temp)
	{
		if (!ft_strcmp(temp->index, index))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
