/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 14:24:08 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node)
	{
		printf("%s %d\n", node->token, node->type);
		node = node->next;
	}
}

int	ft_process_inputs(t_ms *mini)
{
	ft_load_input(mini);
	ft_workflow(mini);
	ft_print_tree(mini->first_token, 10);
	printf("\n");
	ft_print_tree(mini->first_token, 10);
	printf("\n");
	if (!ft_get_expand(mini, mini->first_token))
		printf("fallo get_expand");
	while (mini->first_token)
	{
		if (mini->first_token->meta <= MTA_BUILDIN)
			ft_build_in(mini);
		else
			ft_out_bin(mini);
	}
	//ft_print_tree(mini->first_token, 10);
	ft_clear_nodes(mini);
	return (SUCCESS);
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
			if (mini->line)
				free (mini->line);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	mini;

	(void) argc;
	(void) argv;

	ft_init_minishell(&mini, envp);
	ft_env_to_list(envp, &mini);
	if (set_signal(&mini))
		return (0);
	ft_get_input(&mini);
	return (0);
}	
