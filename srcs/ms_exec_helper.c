/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:39:59 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/22 11:09:27 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_ms_vars	*g_msvars;

t_redirect	*reverse_redirect(t_redirect *redirect)
{
	t_redirect	*prev;
	t_redirect	*next;
	t_redirect	*cursor;

	if (redirect == NULL)
		return (NULL);
	prev = redirect;
	cursor = redirect->next;
	prev->next = NULL;
	while (cursor != NULL)
	{
		next = cursor->next;
		cursor->next = prev;
		prev = cursor;
		cursor = next;
	}
	return (prev);
}

t_command	*reverse_command(t_command *command_line)
{
	t_command	*prev;
	t_command	*next;
	t_command	*cursor;

	if (command_line == NULL)
		return (NULL);
	prev = command_line;
	cursor = command_line->next;
	prev->next = NULL;
	while (cursor != NULL)
	{
		next = cursor->next;
		cursor->next = prev;
		prev = cursor;
		cursor = next;
	}
	return (prev);
}

void	sent_directory(int *pipefd)
{
	char	*str;

	close(pipefd[0]);
	str = NULL;
	str = getcwd(str, 0);
	write(pipefd[1], str, ft_strlen(str) + 1);
	close(pipefd[1]);
	free(str);
}

void	set_directory(int *pipefd)
{
	char	str[1024];

	close(pipefd[1]);
	read(pipefd[0], str, 1024);
	close(pipefd[0]);
	chdir(str);
	setvar("PWD", str, g_msvars->env_lst);
}
