/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:48:21 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/11 15:35:10 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo devuelve 0 si ha ido todo bien y devuelve> 0 si ocurrio algun error
int	ft_echo(t_ms *mini)
{
	char	*input;
	char	*opcion;
	int		ret;

	ret = 0;
	input = ft_substr(mini->line, 5, ft_strlen(mini->line));
	//buscamos opcion -n
	opcion = ft_substr(mini->line, 5, 7);

	if (!ft_strncmp(opcion, "-n", 2))
	{
		input = ft_substr(mini->line, 8, ft_strlen(mini->line));
		printf("%s",input);
	}
	else	
		printf("%s\n",input);
	free(input);
	return (ret);
}
