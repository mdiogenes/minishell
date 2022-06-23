/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:44:24 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/22 11:51:49 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrld(t_ms *mini)
{
	mini->exitstatus = 1;
	rl_on_new_line();
	rl_redisplay();
	ft_free_exit(mini);
	printf("exit");
	exit (0);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	if (signum == SIGQUIT)
		rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	set_signal(t_ms *mini)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (ERROR);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (ERROR);
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (ft_error_free(errno, mini));
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		return (ft_error_free(errno, mini));
	return (SUCCESS);
}
