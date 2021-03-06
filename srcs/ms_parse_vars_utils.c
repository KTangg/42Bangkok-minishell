/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_vars_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:12:11 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 14:03:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

void	setshell(char *name)
{
	char	path[1000];
	char	**shellname;
	int		i;

	i = 0;
	shellname = ft_split(name, '/');
	getcwd(path, 1000);
	while (shellname[i])
		i++;
	i--;
	ft_strlcat(path, "/", 1000);
	ft_strlcat(path, shellname[i], 1000);
	while (i >= 0)
		free(shellname[i--]);
	free(shellname);
	setvar("SHELL", path, NULL);
}

char	*getshell(void)
{
	char	*value;
	char	**path;
	int		i;
	char	*output;

	i = 0;
	value = getvar("SHELL");
	path = ft_split(value, '/');
	while (path[i])
		i++;
	i--;
	output = ft_strdup(path[i]);
	while (i >= 0)
		free(path[i--]);
	free(path);
	return (output);
}

void	set_shlvl(void)
{
	int		lvl;
	char	*lvlvar;

	lvlvar = getvar("SHLVL");
	if (!lvlvar)
		return ;
	lvl = ft_atoi(lvlvar);
	lvl++;
	lvlvar = ft_itoa(lvl);
	setvar("SHLVL", lvlvar, g_msvars->env_lst);
	free(lvlvar);
}
