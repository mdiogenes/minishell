/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:17:56 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/16 15:47:33 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ms *mini)
{
	size_t	size;
	int	i;
	char	*temp;

	i = 0;
	size = ft_count_node(mini);
	if (size != 1)
		return(ft_error_comands(mini->first_token->token, MSG_MANY_ARG));
	else
	{
		if (mini->dupenvp)
		{	
			while (mini->dupenvp[i]!=NULL)
			{
        		        temp = mini->dupenvp[i];
				if (temp)
					printf("\n%s", temp);
        		        i ++;
        		}
			printf("\n");
		}
	}
	ft_process_branch(mini);
	return (1);
}
