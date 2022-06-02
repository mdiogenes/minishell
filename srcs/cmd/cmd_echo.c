/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:48:21 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/31 12:41:37 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo devuelve 0 si ha ido todo bien y devuelve> 0 si ocurrio algun error
int	ft_echo(t_ms *mini)
{
	t_token	*token;
	int		ret;
	int		opcio;

	opcio = 0;
	ret = 0;
	token = mini->first_token;
	if (token->args && (ft_strncmp(token->args->token, "-n", 1) == 0))
	{
		opcio = 1;
		token->args = token->args->next;
	}
	while (token->args)
	{
		if (opcio == 0)
			printf("%s\n", token->args->token);
		if (opcio == 1)
			printf("%s", token->args->token);
		token->args = token->args->next;
	}
	ft_export_var("?", "0", SYS_HIDDEN, mini);
	ft_process_branch(mini);
	return (ret);
}
