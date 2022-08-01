/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 10:29:14 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	**ft_build_pipes(int n, t_ms *mini)
{
	int	**rst;

	ft_free_pipes(mini);
	rst = (int **)malloc(sizeof(int *) * (n + 1));
	if (!rst)
		ft_error_free(errno, mini);
	rst[n] = NULL;
	while (n--)
		rst[n] = (int *)malloc(sizeof(int) * 2);
	return (rst);
}

static inline int	ft_count_pipes(t_ms *mini)
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
		i = 1;
	else
		i--;
	mini->pipes = ft_build_pipes(i, mini);
	return (i);
}

static inline void	ft_deal_pipes(t_token *token, t_ms *mini, int n, int scn)
{
	if (scn == 0)
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		return ;
	}
	if (token->in == TKN_PIPEIN)
		close(mini->pipes[n - 1][PIPE_READ]);
	if (token->out == TKN_PIPEOUT)
		close(mini->pipes[n][PIPE_WRITE]);
	ft_process_branch(mini);
}

int	ft_deal_fork(t_token *token, t_ms *mini, int *total)
{
	if (mini->pid_child == -1)
		return (ERROR);
	if (token->type == IMP_HEREDOC)
		*(total) = *(total) - 1;
	return (SUCCESS);
}

int	ft_pipes(t_ms *mini)
{
	t_token	*token;
	int		n;
	int		total;
	pid_t	child;

	total = ft_count_pipes(mini);
	n = 0;
	child = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		ft_deal_pipes(token, mini, n, 0);
		mini->pid_child = ft_fork_and_run(mini, n, NULL, ft_heredoc_monitor);
		if (ft_deal_fork(token, mini, &total) == ERROR)
			return (ERROR);
		if (mini->first_token->sp_tkn != SILENCED_CHECK)
			child = mini->pid_child;
		ft_deal_pipes(token, mini, n, 1);
		token = mini->first_token;
		ft_prepare_node(mini, token);
		n++;
	}
	close(mini->pipes[n - 2][PIPE_READ]);
	ft_child_monitor(mini, total + 1, child);
	return (SUCCESS);
}
