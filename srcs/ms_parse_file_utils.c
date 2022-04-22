/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:33:29 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 18:44:34 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_insiout(t_command *target, t_command *cur);
static void	lst_insfout(t_command *target, t_command *cur);
static char	*checkfilewild(char *cmd, int *iswild);

void	move_filecmd(t_command *cur, t_command *target)
{
	if (cur->command && *cur->command)
	{
		if ((cur->redirection == 2 || cur->redirection == 3))
			lst_insfout(target, cur);
		else if ((cur->redirection == 1 || cur->redirection == 4))
			lst_insiout(target, cur);
	}
	else if (cur->next == NULL)
		print_synterr("newline");
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
			if (wild == NULL)
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

static char	*checkfilewild(char *cmd, int *iswild)
{
	char	**filelist;
	int		size;
	int		i;
	char	*output;

	i = 0;
	*iswild = check_wild(cmd);
	if (*iswild == 0)
		return (NULL);
	filelist = expand_wild(cmd);
	size = getarrsize(filelist);
	if (size <= 1)
	{
		output = filelist[0];
		free(filelist);
		return (output);
	}
	while (i < size)
		free(filelist[i++]);
	free(filelist);
	if (size == 0)
		*iswild = 0;
	*iswild = 1;
	return (NULL);
}
