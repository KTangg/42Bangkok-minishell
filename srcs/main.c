/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:38:13 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/31 18:28:46 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

// Signal handling function
static void	sig_handle(int signo, siginfo_t *info, void *other)
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
		return ;
}

// Exiting Shell via CTRL + D
static void	shell_exit(void)
{
	rl_clear_history();
	printf("\n");
	// Free global struct
	exit(0);
}

// Initial terminal attribute
// Not echo ctrl command
static void	init_term(struct termios term)
{
	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
}

// Initial signal handler
static void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handle;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	struct termios		term;

	(void)argc;
	(void)argv;
	(void)envp;
	//info = init_info(envp);
	init_term(term);
	init_signal();
	while (1)
	{
		line = readline("hello: ");
		if (!line)
			shell_exit();
		if (line[0] != '\0')
		{
			add_history(line);
			//execute_line(line);
		}
		free(line);
	}
}
