/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:10:56 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(t_ms *mini, char token)
{
	ft_putstr_fd("ms-42 : syntax error near unexpected token `", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	mini->exitstatus = 258;
	return (mini->exitstatus);
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
	printf("ms-42 Error: %s\n", strerror(error));
	ft_process_branch(mini);
	mini->exitstatus = 1;
	return (ERROR);
}

int	ft_error_free(int error, t_ms *mini)
{
	printf("ms-42 Error: %s\n", strerror(error));
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
	return (mini->exitstatus);
}

void	ft_error_general(char *msg, t_ms *mini)
{
	printf("ms-42 Error: %s\n", msg);
	ft_free_exit(mini);
	mini->exitstatus = 1;
	exit (mini->exitstatus);
}
