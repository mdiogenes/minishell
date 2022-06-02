/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/12 21:21:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_exec(t_ms *mini, char **argv, int n)
{
	if (mini->first_token->out == TKN_PIPEOUT)
	{
		dup2(mini->pipes[n][PIPE_WRITE], STDOUT_FILENO);
		close(mini->pipes[n][PIPE_READ]);
		close(mini->pipes[n][PIPE_WRITE]);
	}
	if (mini->first_token->in == TKN_PIPEIN)
	{
		dup2(mini->pipes[n - 1][PIPE_READ], STDIN_FILENO);
		close(mini->pipes[n - 1][PIPE_READ]);
		close(mini->pipes[n - 1][PIPE_WRITE]);
	}
	if (mini->first_token->type == RDR_TO_FILE
		|| mini->first_token->type == RDR_APP_FILE)
		ft_dup_file(mini);
	else if (mini->first_token->type == IMP_FROM_FILE)
		ft_inp_from_file(mini);
	else if (mini->first_token->type == IMP_HEREDOC)
		ft_heredoc(mini);
	execve(argv[0], argv, NULL);
	ft_error_handler(errno, mini);
	exit (ERROR);
}

int	**ft_build_pipes(int n, t_ms *mini)
{
	int	**rst;

	rst = (int **)malloc(sizeof(int *) * n);
	if (!rst)
		ft_error_free(errno, mini);
	while (n--)
		rst[n] = (int *)malloc(sizeof(int) * 2);
	return (rst);
}

int	ft_count_pipes(t_ms *mini)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		i++;
		token = token->next;
	}
	if (i < 2)
		return (1);
	return (i - 1);
}

int	ft_control_pipeline(t_ms *mini, int n)
{
	int	status;
	int sig;

	close(mini->pipes[n - 1][PIPE_READ]);
	close(mini->pipes[n - 1][PIPE_WRITE]);
	waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) != 0)
		{
			sig = WTERMSIG(status);
			ft_child_signals_msg(sig);
		}
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) != 0)
		{
			sig = WTERMSIG(status);
			ft_child_signals_msg(sig);
		}
	return (SUCCESS);
}

int	ft_pipes(t_ms *mini)
{
	pid_t	cpid;
	char	**argv;
	t_token	*token;
	int		n;

	mini->pipes = ft_build_pipes(ft_count_pipes(mini), mini);
	n = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		argv = ft_build_argv(mini, token);
		cpid = fork();
		if (cpid == 0)
			ft_pipe_exec(mini, argv, n);
		if (token->in == TKN_PIPEIN)
			ft_control_pipeline(mini, n);
		free(argv);
		ft_process_branch(mini);
		token = mini->first_token;
		n++;
	}
	return (SUCCESS);
}
