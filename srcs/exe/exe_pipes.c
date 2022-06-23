/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/22 13:44:03 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(t_ms *mini, int n)
{
	close(mini->pipes[n][PIPE_READ]);
	close(mini->pipes[n][PIPE_WRITE]);
}

static inline int	**ft_build_pipes(int n, t_ms *mini)
{
	int	**rst;

	rst = (int **)malloc(sizeof(int *) * n);
	if (!rst)
		ft_error_free(errno, mini);
	while (n--)
	{
		rst[n] = (int *)malloc(sizeof(int) * 2);
		if (!rst[n])
			ft_error_free(errno, mini);
	}
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
		return (1);
	return (i - 1);
}

int	ft_pipes(t_ms *mini)
{
	t_token	*token;
	int		n;

	mini->pipes = ft_build_pipes(ft_count_pipes(mini), mini);
	n = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		ft_fork_and_run(mini, n, ft_process_branch);
		token = mini->first_token;
		n++;
	}
	return (SUCCESS);
}
