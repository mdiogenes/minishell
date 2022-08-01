/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:44:24 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/07 14:14:34 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrld(t_ms *mini)
{
	long long int	exit_sts;

	if (g_mini->pid_child == 0)
	{
		exit_sts = mini->exitstatus;
		rl_on_new_line();
		rl_redisplay();
		ft_free_exit(mini);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit (exit_sts);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT && g_mini->process == IMP_HEREDOC)
	{
		ft_safe_free_char(&g_mini->first_token->stored);
		ft_safe_free_char(&g_mini->stored);
		ft_putendl_fd("", STDERR_FILENO);
		exit (1);
	}
	if (signum == SIGINT && g_mini->pid_child == 0)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	set_signal(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (ft_error_signals(errno, g_mini));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ft_error_signals(errno, g_mini));
	return (SUCCESS);
}
