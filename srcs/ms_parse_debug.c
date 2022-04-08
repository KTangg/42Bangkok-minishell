/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:07:35 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/08 15:21:42 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_files(t_command *cmd);
static void	print_cmdval(t_command *cmd);

void	print_cmdlst(t_command *cmdlist)
{
	t_command	*temp;
	int			i;
	int			j;
	t_command	*clean;

	i = 0;
	temp = cmdlist;
	while (temp)
	{
		j = 0;
		printf("[Command %i] - ", i++);
		while ((temp->command)[j])
		{
			printf("%i:[%s] ", j, (temp->command)[j]);
			free(temp->command[j]);
			j++;
		}
		print_cmdval(temp);
		free(temp->command);
		clean = temp;
		temp = temp->next;
		free(clean);
	}
}

static void	print_cmdval(t_command *cmd)
{
	printf(" - Redirection: %i ", cmd->redirection);
	printf("Recursion: %i\n", cmd->recursive);
	print_files(cmd);
	if (cmd->output)
		clean_cmdfiles(cmd->output);
	if (cmd->input)
		clean_cmdfiles(cmd->input);
}

static void	print_files(t_command *cmd)
{
	t_redirect	*tempred;

	if (cmd->output)
	{
		printf("File output: ");
		tempred = cmd->output;
		while (tempred)
		{
			printf("■ %s Type: %i ", tempred->file, tempred->redirect);
			tempred = tempred->next;
		}
		printf("\n");
	}
	if (cmd->input)
	{
		printf("File input: ");
		tempred = cmd->input;
		while (tempred)
		{
			printf("■ %s Type: %i ", tempred->file, tempred->redirect);
			tempred = tempred->next;
		}
		printf("\n");
	}
}
