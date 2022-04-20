/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:38:30 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 16:34:55 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ls_print(char *filename);
static int	ls_flags(char **argv);
static void	ls_color(struct dirent *finfo);

int	cmd_ls(char **argv)
{
	void			*fd;
	char			path[1024];
	struct dirent	*finfo;
	int				flags;

	flags = ls_flags(argv);
	if (flags <= 0)
		return (flags);
	fd = opendir(getcwd(path, 1024));
	if (!fd)
		return (-1);
	finfo = readdir(fd);
	while (finfo)
	{
		ls_color(finfo);
		ls_print(finfo->d_name);
		printf("\e[0m");
		finfo = readdir(fd);
	}
	ls_print(NULL);
	closedir(fd);
	return (0);
}

static void	ls_color(struct dirent *finfo)
{
	struct stat	f_stat;

	if (finfo->d_type == DT_DIR)
		printf("\e[1;34m");
	else if (stat(finfo->d_name, &f_stat) == 0)
		if (f_stat.st_mode && (f_stat.st_mode & S_IXUSR))
			printf("\e[1;32m");
	return ;
}

static int	ls_flags(char **argv)
{
	int	check;

	if (!argv[1])
		return (1);
	check = (!ft_strcmp(argv[1], "-v") || !ft_strcmp(argv[1], "--version"));
	if (argv[1] && check && !argv[2])
	{
		printf("--- ls ---\n");
		printf("built-in function of 42 project's minishell\n");
		return (0);
	}
	else if (argv[1])
		return (-1);
	return (1);
}

static void	ls_print(char *filename)
{
	static int	column = 0;

	if (!filename)
	{
		column = 0;
		printf("\n");
		return ;
	}
	if (filename[0] != '.')
	{
		printf("%-20s", filename);
		column++;
	}
	else
		return ;
	if (column > 7)
	{
		column = 0;
		printf("\n");
	}
}
