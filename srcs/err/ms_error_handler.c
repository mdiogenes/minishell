/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:09:37 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(t_ms *mini, char token, int rpt)
{
	ft_putstr_fd("ms-42 : syntax error near unexpected token `", STDERR_FILENO);
	if (token == '\n')
		ft_putstr_fd("newline", STDERR_FILENO);
	else
	{
		while (rpt--)
			ft_putchar_fd(token, STDERR_FILENO);
	}
	ft_putstr_fd("'\n", STDERR_FILENO);
	mini->exitstatus = 258;
	return (ERROR);
}

int	ft_error_unset_var(char *msg, t_token *token, t_ms *mini)
{
	ft_putstr_fd("ms-42 ", STDERR_FILENO);
	ft_putstr_fd("unset : `", STDERR_FILENO);
	if (token->token)
		ft_putstr_fd(token->token, STDERR_FILENO);
	if (token->args)
	{
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putstr_fd(token->args->token, STDERR_FILENO);
	}
	ft_putstr_fd("' ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	mini->exitstatus = 1;
	ft_process_branch(mini);
	return (mini->exitstatus);
}

int	ft_error_handler(int error, t_ms *mini)
{
	ft_putstr_fd("ms-42 Error:", STDERR_FILENO);
	ft_putstr_fd(strerror(error), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_process_branch(mini);
	mini->exitstatus = 1;
	return (ERROR);
}

int	ft_error_free(int error, t_ms *mini)
{
	ft_putstr_fd("ms-42 Error:", STDERR_FILENO);
	ft_putstr_fd(strerror(error), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
	return (mini->exitstatus);
}

void	ft_error_general(char *msg, t_ms *mini)
{
	ft_putstr_fd("ms-42 Error:", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
}
