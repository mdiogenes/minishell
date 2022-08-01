/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:26:33 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/26 22:26:34 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_exit_heredoc(t_ms *mini)
{
	ft_safe_free_char(&mini->stored);
	ft_safe_free_char(&mini->first_token->stored);
	write(STDIN_FILENO, "\n", 1);
	exit(-1);
}

static inline void	ft_clear_heredoc(t_ms *mini)
{
	if (mini->exitstatus == 1)
		ft_clear_nodes(&mini->first_token, &mini->last_token);
	else
	{
		while (mini->first_token && mini->first_token->meta < MTA_NEXT)
			ft_process_branch(mini);
	}
}

int	ft_heredoc_monitor(t_ms *mini, int n, pid_t pid_child)
{
	int		status;
	pid_t	child;

	if (n > -1 && mini->first_token->type != IMP_HEREDOC)
		return (SUCCESS);
	child = waitpid(pid_child, &status, 0);
	if (WEXITSTATUS(status) == 0 && WIFSIGNALED(status) == 0)
		return (SUCCESS);
	if (WEXITSTATUS(status) == 255 && WIFSIGNALED(status) == 0)
		mini->exitstatus = 0;
	else if (WEXITSTATUS(status) == 1 && WIFSIGNALED(status) == 0)
		mini->exitstatus = 1;
	if (mini->exitstatus > 0 && WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) != 13)
			ft_child_signals_msg(WTERMSIG(status));
		else
			mini->exitstatus = 127;
	}
	mini->process = 0;
	mini->pid_child = -1;
	ft_clear_heredoc(mini);
	return (ERROR);
}

int	ft_heredoc(t_ms *mini)
{
	mini->process = IMP_HEREDOC;
	mini->first_token->args->token
		= ft_strjoin_clean_one(&mini->first_token->args->token, "\n");
	ft_safe_free_char(&mini->stored);
	ft_safe_free_char(&mini->first_token->stored);
	while (1)
	{
		write(STDIN_FILENO, "\e[32mms-42_heredoc>\e[0m ", 24);
		mini->first_token->stored = get_next_line(STDIN_FILENO);
		if (!mini->first_token->stored)
			ft_exit_heredoc(mini);
		if (ft_strict_cmp(mini->first_token->stored,
				mini->first_token->args->token) == 0)
			break ;
		mini->stored = ft_strjoin_clean(&mini->stored,
				&mini->first_token->stored, 0);
	}
	if (mini->first_token->out == TKN_PIPEOUT)
		ft_putstr_fd(mini->stored, STDOUT_FILENO);
	ft_safe_free_char(&mini->stored);
	ft_safe_free_char(&mini->first_token->stored);
	return (SUCCESS);
}
