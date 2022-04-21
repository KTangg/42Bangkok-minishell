/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:26:57 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/21 13:50:01 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_cmdapp(t_command *cmd, char **toapp);
static void	lst_insfout(t_command *target, t_command *cur);
static void	lst_insiout(t_command *target, t_command *cur);
static char	*checkfilewild(char *cmd, int *iswild);

t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur)
{
	t_command	*prev;
	t_command	*target;

	prev = cmdlst;
	target = cur->next;
	if (prev != cur)
		while (prev->next != cur)
			prev = prev->next;
	if (cur->redirection == 2 || cur->redirection == 3)
		lst_insfout(target, cur);
	else if (cur->redirection == 1 || cur->redirection == 4)
		lst_insiout(target, cur);
	lst_cmdapp(target, &(cur->command[1]));
	free(cur->command[0]);
	if (prev != cur)
		prev->next = target;
	free(cur->command);
	if (cur == prev)
	{
		free(cur);
		return (target);
	}
	return (cmdlst);
}

// Insert file out into front of list
// The resulting file redirection will have the redirect flag set:
// 1 - File is a target for file in ('>')
// 2 - File is a target for appending ('>>')
static void	lst_insfout(t_command *target, t_command *cur)
{
	char	*wild;
	int		iswild;

	wild = checkfilewild(cur->command[0], &iswild);
	*(cur->command) = strip_cmd(*(cur->command));
	if (target->output == NULL)
	{
		target->output = (t_redirect *)malloc(sizeof(t_redirect));
		if (iswild)
		{
			target->output->file = wild;
			print_wilderr(*(cur->command));
		}
		else
			target->output->file = ft_strdup(cur->command[0]);
		if (cur->redirection == 2 && target)
			target->output->redirect = 1;
		else if (cur->redirection == 3 && target)
			target->output->redirect = 2;
		target->output->next = cur->output;
	}
	if (cur->input)
		target->input = cur->input;
}

// Insert file in into front of list
// The resulting file redirection will have the redirect flag set:
// 1 - File is a target for file in ('<')
// 2 - File is a target for appending ('<<')
static void	lst_insiout(t_command *target, t_command *cur)
{
	int		iswild;
	char	*wild;

	wild = checkfilewild(cur->command[0], &iswild);
	*(cur->command) = strip_cmd(*(cur->command));
	if (target->input == NULL)
	{
		target->input = (t_redirect *)malloc(sizeof(t_redirect));
		if (iswild)
		{
			target->output->file = wild;
			print_wilderr(*(cur->command));
		}
		else
			target->input->file = ft_strdup(cur->command[0]);
		if (cur->redirection == 1 && target)
			target->input->redirect = 1;
		else if (cur->redirection == 4 && target)
			target->input->redirect = 2;
		target->input->next = cur->input;
	}
	if (cur->output)
		target->output = cur->output;
}

static void	lst_cmdapp(t_command *cmd, char **toapp)
{
	int		arr_size;
	int		i;
	char	**newargv;

	arr_size = 0;
	i = 0;
	while (cmd->command[arr_size])
		arr_size++;
	while (toapp[i])
		i++;
	newargv = (char **)malloc((arr_size + i + 1) * sizeof(char *));
	arr_size = 0;
	while (cmd->command[arr_size])
	{
		newargv[arr_size] = cmd->command[arr_size];
		arr_size++;
	}
	free(cmd->command[arr_size]);
	i = 0;
	while (toapp[i])
		newargv[arr_size++] = toapp[i++];
	newargv[arr_size] = toapp[i];
	free(cmd->command);
	cmd->command = newargv;
}

static char	*checkfilewild(char *cmd, int *iswild)
{
	char	**filelist;
	int		size;
	int		i;
	char	*output;

	i = 0;
	*iswild = check_wild(cmd);
	filelist = expand_wild(cmd);
	size = getarrsize(filelist);
	if (size > 1)
	{
		while (i < size)
			free(filelist[i++]);
		free(filelist);
		return (NULL);
	}
	else if (size == 1)
	{
		output = filelist[0];
		free(filelist);
		return (output);
	}
	*iswild = 0;
	return (NULL);
}
