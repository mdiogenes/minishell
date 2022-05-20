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

size_t	ft_count_args(t_token *token)
{
	size_t	i;
	t_token	*node;

	i = 1;
	if (token->args == NULL)
		return (1);
	node = token->args;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

char	**ft_build_argv(t_ms *mini, t_token *token)
{
	size_t	size;
	size_t	i;
	t_token	*node;
	char	**rst;

	size = ft_count_args(mini->first_token);
	i = 1;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	rst[0] = token->token;
	node = token->args;
	while (node)
	{
		rst[i] = node->token;
		node = node->next;
		i++;
	}
	return (rst);
}

int	ft_loader_exe(t_ms *mini, char *argv[], char *argenv[])
{
	if (execve(mini->first_token->token, argv, argenv) == -1)
		ft_error_handler(errno);
	exit (ERROR);
}

int	ft_fork_and_run(t_ms *mini)
{
	pid_t	fork_pid;
	char	**argv;
	char	**argenv;
	int		rst;

	argv = ft_build_argv(mini, mini->first_token);
	argenv = ft_build_argv(mini, mini->first_token);
	fork_pid = fork();
	if (fork_pid > 0)
	{
		waitpid(fork_pid, &rst, WUNTRACED);
		ft_clear_tabs(argv);
		ft_clear_tabs(argenv);
		ft_process_branch(mini);
		return (WEXITSTATUS(rst));
	}
	if (fork_pid == 0)
		ft_loader_exe(mini, argv, argv);
	return (SUCCESS);
}
