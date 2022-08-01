/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:51:22 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/16 15:52:25 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_opt_error(t_ms *mini, t_token *node)
{
	ft_putchar_fd(node->token[0], MS_STDERR);
	if (ft_strlen_max(node->token, 2) == 2)
		ft_putchar_fd(node->token[1], MS_STDERR);
	else
	{
		if (node->args != NULL)
			ft_putchar_fd('=', MS_STDERR);
	}
	ft_putstr_fd("': invalid option\n", MS_STDERR);
	mini->exitstatus = 2;
	return (ERROR);
}

int	ft_export_id_error(t_ms *mini, t_token *node)
{
	if (ft_strlen_max(node->token, 1) == 0)
		return (ERROR);
	ft_putstr_fd("ms-42 : export `", MS_STDERR);
	if (node->meta != MTA_NULL_TOKEN && node->token[0] == '-')
		return (ft_export_opt_error(mini, node));
	if (node->args)
	{
		ft_putstr_fd(node->token, MS_STDERR);
		ft_putstr_fd("=", MS_STDERR);
		ft_putstr_fd(node->args->token, MS_STDERR);
	}
	else
		ft_putstr_fd(node->token, MS_STDERR);
	ft_putstr_fd("': not a valid identifier\n", MS_STDERR);
	mini->exitstatus = 1;
	return (ERROR);
}

int	ft_error_export_var(t_token *token, t_ms *mini)
{
	ft_putstr_fd("ms-42 ", MS_STDERR);
	ft_putstr_fd("export : `", MS_STDERR);
	if (token->token)
		ft_putstr_fd(token->token, MS_STDERR);
	if (token->args)
	{
		ft_putstr_fd("=", MS_STDERR);
		ft_putstr_fd(token->args->token, MS_STDERR);
	}
	ft_putstr_fd("' ", MS_STDERR);
	ft_putstr_fd(MSG_ERR_IDNT, MS_STDERR);
	ft_putstr_fd("\n", MS_STDERR);
	mini->exitstatus = 1;
	return (ERROR);
}
