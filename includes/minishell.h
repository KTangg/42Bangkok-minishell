/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:48 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 13:04:15 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// Define Redirection Code
# define REDIRIN 1
# define REDIROUT 2
# define REDIRAPP 3
# define REDIRHRE 4
# define REPIPE 5
# define REAND 6
# define REOR 7
# define HERE_DOCFILE "here_doc.txt"

// Define Exit Status
# define EXIT_EXIT 254
# define FORK_FAIL 253
# define PIPE_FAIL 252
# define FILE_FAIL 251
# define CMD_NOT_FOUND 127
# define EXIT_SIGINT 130

// Outmode: 0 - Do nothing; 1 - '>' to file; 2 - '>>' to file;
// Inmode: 0 - Do nothing; 1 - '<' read from file; 2 - '<<' Here Document
typedef struct s_redirect {
	char				*file;
	int					redirect;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	int					redirection;
	t_redirect			*output;
	t_redirect			*input;
	char				**command;
	int					recursive;
	struct s_command	*next;
	struct s_command	*next_pipe;
}	t_command;

typedef struct s_vars {
	char			*index;
	char			*value;
	struct s_vars	*next;
}	t_vars;

typedef struct s_ms_vars {
	int		fork;
	int		dup_fd[2];
	int		status;
	int		exit_status;
	char	**environ;
	t_vars	**env_lst;
	t_vars	**var_lst;
}	t_ms_vars;

typedef struct s_parexcp {
	int	sq_open;
	int	dq_open;
	int	p_open;
	int	any_open;
}	t_parexcp;

typedef struct s_searched {
	char	*str;
	int		searched;
	int		viable;
}	t_searched;

char		*getprompt(void);
void		shell_exit(void);

// Line Process Prototype
int			shell_line(char *line);

// Execute Process Prototype
int			recursive_exec(char *line);
int			execute_execve(char *argv[]);
int			redir_execute(t_command *command_line);
int			execute_final(t_command *command_line);

// Split Process Prototype
t_ms_vars	*init_global(char **envp);
t_command	*parse_seqcmds(char *line);
t_command	*checkcmdlst(t_command *cmdlist);
t_command	*lst_cmdfile(t_command *cmdlst, t_command *cur);
void		print_varlist(t_vars **lst);
void		print_cmdlst(t_command *cmdlist);
void		print_synterr(const char *str);
void		setshell(char *name);
void		init_parexcp(t_parexcp *p);
void		ms_cleanup_global(void);
void		init_cmd(t_command *cmd);
void		clean_cmdfiles(t_redirect *target);
void		built_printerr(char *cmd, char *arg);
void		set_shlvl(void);
char		**split_args(const char *line, int len);
char		**lst_delcmd(t_command *cmdlist, char *cmd);
char		*getshell(void);
int			checkredir(const char *line, int len);
int			isredir(const char c);
int			getcmdlen(const char *line, int *pos, int *recursive);
int			isquoting(char c, t_parexcp *p);

// Variables Handling Prototypes
void		app_var(t_vars **lst, char *index, char *value);
void		setvar(char *index, char *value, t_vars **lst);
void		parsevarset(char *cmd, t_vars **lst);
void		unsetvar(char *index, int lst);
void		set_environ(char *index, char *value);
void		add_environ(char *index, char *value, int size);
void		cmd_varerr(char *cmd, char *arg);
void		strip_quote(char **cmdlist);
void		print_wilderr(const char *str);
char		*expand_var(char *line);
char		*getvar(char *index);
char		**get_wild(char **cmdchain);
char		**arr_app(char **chain, char **newcmd);
char		**cmd_app(char **arr, char *str);
char		*strip_cmd(char *cmd);
char		**get_wild_any(void);
char		**get_wild_patt(char *cmd);
char		**expand_wild(char *cmd);
int			validvarn(char c, int pos, int set);
int			isvarset(char *cmd);
int			getarrsize(char **arr);
int			check_varn(char *name);
int			check_wild(char *cmd);
int			checkrepeat(char **arr, int size, char *str);

// Builtin Commands Prototypes
int			is_builtin(char **cmdchain);
int			execute_built(char **argv);
int			cmd_env(char **argv, char **envp);
int			cmd_echo(char **argv, char **envp);
int			cmd_exit(char **argv);
int			cmd_cd(char **argv);
int			cmd_unset(char **argv);
int			cmd_export(char **argv);
int			cmd_pwd(char **argv);
int			cmd_ls(char **argv);

// Exec Helper
void		set_directory(int *pipefd);
void		sent_directory(int *pipefd);
int			check_execute(t_command *command_line);
t_command	*reverse_command(t_command *command_line);
t_redirect	*reverse_redirect(t_redirect *redirect);

// Redirection Prototype
int			redir_out(char *path);
int			redir_app(char *path);
int			redir_inp(char *path);
int			here_document(char *end);

// Pipe | Operation Prototype
int			redir_pipe(t_command *left_cmd, t_command *right_cmd);

// Section Command Prototype
int			section_execute(t_command *cmd_section);
int			section_list(t_command *cmd_list);
t_command	*section_command(t_command *cmd_list);

#endif
