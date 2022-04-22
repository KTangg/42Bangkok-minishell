/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:25:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 18:50:44 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**getsorted(char **unsorted);

char	**get_wild(char **cmdchain)
{
	int		size;
	int		i;
	char	**newcmd;
	char	**newchain;

	if (!cmdchain || !(*cmdchain))
		return (cmdchain);
	size = getarrsize(cmdchain);
	i = 0;
	newchain = NULL;
	while (i < size)
	{
		if (check_wild(cmdchain[i]))
		{
			newcmd = expand_wild(cmdchain[i]);
			newchain = arr_app(newchain, newcmd);
		}
		else
			newchain = cmd_app(newchain, cmdchain[i]);
		free(cmdchain[i]);
		i++;
	}
	free(cmdchain);
	return (newchain);
}

int	check_wild(char *cmd)
{
	t_parexcp	parexcp;

	init_parexcp(&parexcp);
	if (!cmd)
		return (0);
	while (*cmd)
	{
		isquoting(*cmd, &parexcp);
		if (*cmd == '*' && !parexcp.any_open)
			return (1);
		cmd++;
	}
	return (0);
}

char	**expand_wild(char *cmd)
{
	char		**newlst;

	if (!ft_strcmp(cmd, "*"))
		return (get_wild_any());
	newlst = get_wild_patt(cmd);
	if (!newlst)
	{
		newlst = (char **)malloc(sizeof(char *));
		*newlst = NULL;
	}
	return (newlst);
}

char	**get_wild_any(void)
{
	void			*fd;
	char			path[1024];
	struct dirent	*finfo;
	char			**newlst;

	newlst = NULL;
	fd = opendir(getcwd(path, 1024));
	if (!fd)
		return (NULL);
	finfo = readdir(fd);
	while (finfo)
	{
		newlst = cmd_app(newlst, finfo->d_name);
		if (!newlst)
			return (NULL);
		finfo = readdir(fd);
		while (finfo && finfo->d_name[0] == '.')
			finfo = readdir(fd);
	}
	closedir(fd);
	newlst = getsorted(newlst);
	return (newlst);
}

static char	**getsorted(char **unsorted)
{
	char	**sorted;
	char	*low;
	int		pos;
	int		i;

	pos = 0;
	sorted = (char **)malloc((getarrsize(unsorted) + 1) * sizeof(char *));
	while (pos < getarrsize(unsorted))
	{
		i = 0;
		while (pos > 0 && checkrepeat(sorted, pos, unsorted[i]))
			i++;
		low = unsorted[i];
		while (i++ < getarrsize(unsorted))
			if (ft_strcmp(low, unsorted[i - 1]) > 0)
				if (pos == 0 || ft_strcmp(unsorted[i - 1], sorted[pos - 1]) > 0)
					if (pos == 0 || !checkrepeat(sorted, pos, unsorted[i - 1]))
						low = unsorted[i - 1];
		sorted[pos++] = low;
	}
	sorted[pos] = NULL;
	free(unsorted);
	return (sorted);
}
