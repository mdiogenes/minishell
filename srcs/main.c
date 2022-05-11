/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 12:28:02 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node)
	{
		printf("%s\n", node->token);
		node = node->next;
	}
}

int	ft_process_inputs(t_ms *mini)
{
	ft_load_input(mini);
	if (mini->first_token->type == CMD_PWD)
		ft_putendl_fd(mini->path, STDOUT_FILENO);
	if (mini->first_token->type == CMD_CD)
		ft_cd(mini);
	if (mini->first_token->type == CMD_LS)
		ft_ls(mini);
	if (mini->first_token->type == CMD_ECHO)
		ft_echo(mini);
	ft_clear_nodes(mini);
	return (1);
}

int	ft_get_input(t_ms *mini)
{
	using_history();
	while (mini->status == 1)
	{
		mini->line = readline(mini->prompt);
		if (!mini->line)
			signal_ctrld(mini);
		if (mini->line && *mini->line)
		{	
			add_history(mini->line);
			ft_process_inputs(mini);
			free (mini->line);
		}
	}
	return (1);
}

int	main(void)
{
	t_ms	mini;

	ft_init_minishell(&mini);
	if (set_signal(&mini))
		return(0);
	ft_get_input(&mini);
	return (0);
}
