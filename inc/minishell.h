/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:36:51 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/20 10:58:44 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/param.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

# define BUFFER_SIZE 100
# define SUCCESS  1
# define ERROR 0
# define MSG_MANY_ARG "too many arguments"
# define TOKEN_ENUM 15
# define PIPE_WRITE 1
# define PIPE_READ 0
# define TKN_STDIN 0
# define TKN_PIPEIN 1
# define TKN_STDOUT 0
# define TKN_PIPEOUT 1

typedef enum e_cmd
{
	NO_TYPE,
	CMD_LITERAL,
	CMD_EXPAND,
	CMD_ENV_VAR,
	CMD_PWD,
	CMD_CD,
	CMD_LS,
	CMD_ECHO,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXE, 
	RDR_PIPE,
	RDR_TO_FILE,
	RDR_APP_FILE
}	t_cmd;

typedef enum e_meta
{
	MTA_NOTYPE,
	MTA_ARGS,
	MTA_BUILDIN,
	MTA_OUTEXE,
	MTA_REDIR
}	t_meta;

typedef struct s_token
{
	char			*token;
	int				type;
	int				meta;
	char			in;
	char			out;
	struct s_token	*next;
	struct s_token	*args;
} t_token;

typedef struct s_ms
{
	int				**pipes;
	int				status;
	char			*line;
	char			*prompt;
	char			*path;
	char			**dupenvp;
	struct s_token	*first_token;
}	t_ms;

//process
int	ft_build_in(t_ms *mini);
int	ft_out_bin(t_ms *mini);

//DEBUG
# define COUNT 10
void	ft_print_tree(t_token *node, int space);
void    ft_print_argv(char *argv[]);
void	ft_test(t_ms *mini);
//DEBUG

//cleaning
void	ft_clear_pipes(int **pipes);
void	ft_clear_tabs(char **tab);
int		ft_delete_node(t_token *node);
int		ft_process_branch(t_ms *mini);
void	ft_clear_nodes(t_ms *mini);

//workflow
void ft_workflow(t_ms *mini);

char **ft_build_argv(t_ms *mini, t_token *token);
int ft_pipes(t_ms *mini);
int ft_loader_exe(t_ms *mini, char *argv[], char *argenv[]);

//struct utils
void	ft_get_path_prompt(t_ms *mini);
int 	ft_init_minishell(t_ms *mini, char **envp);
void	ft_free_exit(t_ms *mini);

//cmd
int		ft_ls(t_ms *mini);
int		ft_cd(t_ms *mini);
int		ft_echo(t_ms *mini);
int		ft_exit(t_ms *mini);
int		ft_env(t_ms *mini);
//forks
size_t	ft_count_args(t_token *token);
int		ft_fork_and_run(t_ms *mini);

//input
int		ft_load_input(t_ms *mini);
void	ft_get_expand(t_ms *mini);

//directory?
int		ft_read_from_node(char *token);
int		ft_get_meta_type(int type);

// errors
int		ft_error_comands(char *cmd, char *msg);
int		ft_error_handler(int error);
int		ft_error_free(int error, t_ms *mini);

// strings
int		ft_is_reserved(char c);
int	ft_is_buildin(char c);

// list utils
size_t	ft_count_node(t_ms *mini);
void	ft_inp_append(t_token **lst, t_token *new);
t_token	*ft_inp_new(char *cmd, t_ms *mini);

//void	rl_replace_line (const char *text, int clear_undo);
int		set_signal(t_ms *mini);
void	signal_ctrld();

//redir
int ft_dup_file(char *argv[]);

//getnextline
char	*get_next_line(int fd);
int		ft_strlen_gnl(char *s);
char	*ft_substr_gnl(char *s, int start, int len, int *nl_len);
char	*ft_strdup_gnl(char *src, int len);
char	*ft_strjoin_gnl(char *s1, char *s2, int bytes, int *nl_len);
void	*ft_memcpy_gnl(char *dest, char *src, int n);
char	*ft_line_proccess(char **buffer, int bytes, int *nl_len);
char	*ft_buffer_reader(int fd, char **buffer, char *reader, int *nl_len);
char	*ft_delete_line_from_buffer(char **buffer, int *nl_len);
int		ft_get_endline(char *str);
# endif
