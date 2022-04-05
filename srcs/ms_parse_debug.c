/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:07:35 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/05 09:19:20 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdlst(t_command *cmdlist)
{
	t_command	*temp;
	t_command	*clean;
	int			i;
	int			j;

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
		free(temp->command);
		printf(" - Redirection: %i ", temp->redirection);
		printf("File out: %s Mode: %i ", temp->fileout, temp->outmode);
		printf("Recursion: %i\n", temp->recursive);
		clean = temp;
		temp = temp->next;
		free(clean);
	}
}
