/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 00:10:48 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/12 00:10:51 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_args(t_ms *mini)
{
	size_t	i;
	t_token	*node;

	i = 0;
	node = mini->first_token;
	while (node && (node->type <= CMD_ENV_VAR || (i == 0 && node->type == CMD_EXE)))
	{
		i++;
		node = node->next;
	}
	return (i);
}

char **ft_build_argv(t_ms *mini)
{
	size_t	size;
	size_t	i;
	t_token	*node;
	char	**rst;

	size = ft_count_args(mini);
	i = -1;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	node = mini->first_token;
	while (++i < size)
	{
		rst[i] = ft_strdup(node->token);
		if (rst[i] == NULL)
			ft_error_free(errno, mini);
		node = node->next;
	}
	return (rst);
}

int ft_loader_exe(t_ms *mini, char *argv[], char *argenv[])
{
	if (execve(mini->first_token->token, argv, argenv) == -1)
			ft_error_handler(errno);
	exit (ERROR);
}

int ft_fork_and_run(t_ms *mini)
{
	pid_t	fork_pid;
	char	**argv;
	char	**argenv;
	int		rst;

	argv = ft_build_argv(mini);
	argenv = ft_build_argv(mini);
	fork_pid = fork();
	if (fork_pid > 0)
	{
		waitpid(fork_pid, &rst, WUNTRACED);
		ft_clear_tabs(argv);
		ft_clear_tabs(argenv);
		return (WEXITSTATUS(rst));
	}
	if (fork_pid == 0)
		ft_loader_exe(mini, argv, argenv);
	return (SUCCESS);	
}
