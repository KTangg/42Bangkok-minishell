/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:55:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 08:33:29 by tratanat         ###   ########.fr       */
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
		if (!validvarn(cmd[i], i, 1))
			return (0);
		i++;
	}
	return (0);
}

void	parsevarset(char *cmd, t_vars **lst)
{
	int		len_index;
	int		len_value;
	char	*index;
	char	*value;

	len_index = 0;
	while (cmd[len_index] != '=')
		len_index++;
	index = (char *)malloc((len_index + 1) * sizeof(char));
	ft_strlcpy(index, cmd, len_index + 1);
	index[len_index] = '\0';
	len_value = ft_strlen(cmd + len_index + 1);
	value = (char *)malloc((len_value + 1) * sizeof(char));
	ft_strlcpy(value, cmd + len_index + 1, len_value + 1);
	value[len_value] = '\0';
	setvar(index, value, lst);
	free(index);
	free(value);
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
	if (temp && (!lst || lst == g_msvars->env_lst))
		set_environ(index, value);
	if ((!lst && temp == NULL) || lst == g_msvars->var_lst)
	{
		temp = *(g_msvars->var_lst);
		while (temp && ft_strcmp(temp->index, index))
			temp = temp->next;
	}
	if (temp == NULL && (!lst || lst == g_msvars->var_lst))
		app_var(g_msvars->var_lst, index, value);
	else if (temp == NULL && lst)
		app_var(lst, index, value);
	else
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
}

void	set_environ(char *index, char *value)
{
	t_vars	*temp;
	char	*output;
	int		len;
	int		i;

	i = 0;
	temp = *(g_msvars->env_lst);
	while (temp && ft_strcmp(temp->index, index) && i++ >= 0)
		temp = temp->next;
	if (temp)
	{
		free(g_msvars->environ[i]);
		len = ft_strlen(index) + ft_strlen(value) + 2;
		output = (char *)malloc((len) * sizeof(char));
		output[0] = '\0';
		ft_strlcat(output, index, len);
		ft_strlcat(output, "=", len);
		if (value)
			ft_strlcat(output, value, len);
		output[len - 1] = '\0';
		g_msvars->environ[i] = output;
	}
	else if (index)
		add_environ(index, value, i);
}

void	add_environ(char *index, char *value, int size)
{
	int		i;
	char	**newenv;
	char	*output;
	int		len;

	i = -1;
	newenv = (char **)malloc((size + 2) * sizeof(char *));
	free((g_msvars->environ)[size]);
	while (++i < size)
		newenv[i] = (g_msvars->environ)[i];
	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(index) + 2;
	output = (char *)malloc(len * sizeof(char));
	output[0] = '\0';
	ft_strlcat(output, index, len);
	ft_strlcat(output, "=", len);
	if (value)
		ft_strlcat(output, value, len);
	output[len - 1] = '\0';
	newenv[i++] = output;
	newenv[i] = NULL;
	free(g_msvars->environ);
	g_msvars->environ = newenv;
}
