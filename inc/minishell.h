/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:36:51 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 12:27:35 by msoler-e         ###   ########.fr       */
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
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

# define SUCCESS  1
# define ERROR 0

typedef enum e_cmd
{
	NO_TYPE,
	CMD_PWD,
	CMD_CD,
	CMD_LS,
	CMD_ECHO,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT
}	t_cmd;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
} t_token;

typedef struct s_ms
{
	int				fd;
	int				status;
	char			*pwd;
	char			*line;
	char			*prompt;
	char			*path;
	struct s_token	*first_token;
	int				num_tokens;
}	t_ms;

//struct utils
void	ft_clear_nodes(t_ms *mini);
void	ft_get_path_prompt(t_ms *mini);
int 	ft_init_minishell(t_ms *mini);
void	ft_free_exit(t_ms *mini);

//cmd
int		ft_ls(t_ms *mini);
int		ft_cd(t_ms *mini);
int		ft_echo(t_ms *mini);

//input
int		ft_load_input(t_ms *mini);
//directory?
int		ft_read_from_node(char *token);

// errors
int		ft_error_handler(int error);
int		ft_error_free(int error, t_ms *mini);

// strings
int		ft_is_reserved(char c);
//gnl
//void	rl_replace_line (const char *text, int clear_undo);
int		set_signal(t_ms *mini);
void	signal_ctrld();
char	*get_next_line(int fd);
int		ft_strlen_gnl(char *s);
char	*ft_substr_gnl(char *s, int start, int len, int *nl_len);
char	*ft_strdup_gnl(char *src, int len);
char	*ft_strjoin_gnl(char *s1, char *s2, int bytes, int *nl_len);
//void	*ft_memcpy(char *dest, char *src, int n);
char	*ft_line_proccess(char **buffer, int bytes, int *nl_len);
char	*ft_buffer_reader(int fd, char **buffer, char *reader, int *nl_len);
char	*ft_delete_line_from_buffer(char **buffer, int *nl_len);
int		ft_get_endline(char *str);

# endif
