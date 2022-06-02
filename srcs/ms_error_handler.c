/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:31:17 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/27 09:50:50 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_export(t_token *token)
{
	if (token->type == CMD_ASSIGN)
		return (SUCCESS);
	ft_putstr_fd("ms-42 ", STDERR_FILENO);
	ft_putstr_fd("export : `", STDERR_FILENO);
	if (token->type == CMD_ASSIGN_RE)
	{
		if (token->next)
			ft_putstr_fd(token->next->token, STDERR_FILENO);
	}
	if (token->type == CMD_ASSIGN_LE || token->type == CMD_ASSIGN_BE)
	{
		ft_putstr_fd(token->token, STDERR_FILENO);
		if (token->next && token->type == CMD_ASSIGN_LE)
			ft_putstr_fd(token->next->token, STDERR_FILENO);
	}
	ft_putstr_fd("' ", STDERR_FILENO);
	ft_putstr_fd(MSG_ERR_IDNT, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (token->type == CMD_ASSIGN_BE)
	{
		token->type = CMD_ASSIGN_RE;
		return (ft_error_export(token));
	}
	return (ERROR);
}
int	ft_error_comands(char *cmd, char *msg)
{
	ft_putstr_fd("ms-42 ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (ERROR);
}

int	ft_error_handler(int error, t_ms *mini)
{
	printf("ms-42 Error: %s\n", strerror(error));
	ft_export_var("?", "1", SYS_HIDDEN, mini);
	return (ERROR);
}

int	ft_error_free(int error, t_ms *mini)
{
	printf("ms-42 Error: %s\n", strerror(error));
	ft_free_exit(mini);
	exit (0);
	return (ERROR);
}
