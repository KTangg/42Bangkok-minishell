/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:35:42 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/02 12:10:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getarrsize(char **arr);

t_ms_vars	*init_global(char **envp)
{
	int			i;
	t_ms_vars	*ms_global;
	int			var_len;
	int			arr_size;

	i = 0;
	ms_global = (t_ms_vars *)malloc(sizeof(t_ms_vars));
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
		app_var(ms_global->env_lst, ms_global->environ[i++]);
	}
	(ms_global->environ)[i] = NULL;
	return (ms_global);
}

void	app_var(t_vars **lst, char *line)
{
	t_vars	*newvar;
	char	**variable;
	t_vars	*temp;

	newvar = (t_vars *)malloc(sizeof(t_vars));
	variable = ft_split(line, '=');
	newvar->index = variable[0];
	newvar->value = variable[1];
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
