/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:38:13 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:18 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Signal handling function
void	sig_handle(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;

	if (signo == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signo == SIGQUIT)
	{
		return ;
	}
	exit(1);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	struct sigaction	sa;
	struct termios term;

	(void)argc;
	(void)argv;
	(void)envp;
	// Setting Terminal not echo signal ctrl
	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);

	// Signal Control Process
	sa.sa_sigaction = sig_handle;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	// Initialise global struct
	// Main process
	while (1)
	{
		// Prompt readline to get user input
		line = readline("hello: ");
		if (!line)
		{
			rl_clear_history();
			printf("\n");
			exit(0);
		}
		if (line[0] != '\0')
		{
			// Add user input to an history
			add_history(line);
			// Execute user input
			//execute_line(line);
		}
		free(line);
	}
}
