/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:38:13 by spoolpra          #+#    #+#             */
/*   Updated: 2022/04/23 16:06:57 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms_vars	*g_msvars;

// Signal handling function
static void	sig_handle(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	if (signo == SIGINT)
	{
		g_msvars->exit_status = EXIT_SIGINT;
		if (g_msvars->fork != 0)
			exit(EXIT_SIGINT);
		printf("\n");
		if (g_msvars->status == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		unlink(HERE_DOCFILE);
		return ;
	}
	if (signo == SIGQUIT)
		return ;
}

// Exiting Shell via CTRL + D
void	shell_exit(void)
{
	int	fork;

	fork = g_msvars->fork;
	rl_clear_history();
	close(g_msvars->dup_fd[0]);
	close(g_msvars->dup_fd[1]);
	ms_cleanup_global();
	unlink(HERE_DOCFILE);
	if (!fork)
		ft_putendl_fd("exit", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

// Initial terminal attribute && signal && some global variable
static void	init_shell(struct termios term, int argc, char *argv[])
{
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_sigaction = sig_handle;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
	g_msvars->fork = 0;
	g_msvars->dup_fd[0] = dup(STDIN_FILENO);
	g_msvars->dup_fd[1] = dup(STDOUT_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios		term;
	char				*line;
	char				*prompt;

	init_global(envp);
	setshell(argv[0]);
	tcgetattr(STDIN_FILENO, &term);
	init_shell(term, argc, argv);
	while (1)
	{
		prompt = getprompt();
		g_msvars->status = 0;
		line = readline(prompt);
		free(prompt);
		if (!line)
			shell_exit();
		if (line[0] != '\0')
		{
			add_history(line);
			g_msvars->status = 1;
			g_msvars->exit_status = shell_line(line);
			if (g_msvars->exit_status == EXIT_EXIT)
				shell_exit();
		}
	}
}
