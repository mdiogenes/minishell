/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:48:21 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/06 13:17:51 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_echo_print_token(t_token *args, int n, int opcio)
{
	if ((ft_strncmp(args->token, "-n", 2) != 0) || n == 1)
	{
		ft_putstr_fd(args->token, STDOUT_FILENO);
		n = 1;
	}
	if ((opcio == 0 || n == 1))
	{
		if (args && args->null_tkn == NULL_FROM_PARSE)
		{
			if (args->sp_tkn == 0)
				return (n);
			if (args->sp_tkn >= 4)
				ft_putchar_fd(' ', STDOUT_FILENO);
			if (args->next && (args->sp_tkn % 2) != 0)
				ft_putchar_fd(' ', STDOUT_FILENO);
			return (n);
		}
		if (!args->null_tkn && args->next && args->next->null_tkn == 0
			&& (args->sp_tkn % 2) != 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	return (n);
}

static inline int	ft_echo_args(t_token *node, int opcio, int n)
{
	int		i;
	t_token	*args;

	opcio = 2;
	args = node;
	while (args)
	{
		if (args->token != NULL)
		{
			if ((ft_strncmp(args->token, "-n", 2) == 0) && n == 0)
			{
				i = 2;
				while (args->token[i] && args->token[i] == 'n')
					i++;
				if (!args->token[i])
					opcio = opcio + 1;
				else
				n = 1;
			}
			n = ft_echo_print_token(args, n, opcio);
		}
		args = args->next;
	}
	return (opcio);
}

int	ft_echo(t_ms *mini)
{
	int		opcio;
	int		n;

	n = 0;
	opcio = 0;
	opcio = ft_echo_args(mini->first_token->args, opcio, n);
	if (opcio % 2 == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_process_branch(mini);
	return (SUCCESS);
}
