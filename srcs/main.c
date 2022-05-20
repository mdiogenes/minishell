/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/20 10:58:39 by msoler-e         ###   ########.fr       */
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
	ft_get_expand(mini);
	
	while (mini->first_token)
	{
		if (mini->first_token->type == CMD_PWD)
			ft_putendl_fd(mini->path, STDOUT_FILENO);
		if (mini->first_token->type == CMD_CD)
			ft_cd(mini);
		if (mini->first_token->type == CMD_LS)
			ft_ls(mini);
		if (mini->first_token->type == CMD_EXIT)
			ft_exit(mini);
		if (mini->first_token->type == CMD_ECHO)
			ft_echo(mini);
		if (mini->first_token->type == CMD_ENV)
			ft_env(mini);
		if (mini->first_token->type == CMD_EXE)
		{
			if (mini->first_token->meta == MTA_BUILDIN)
				ft_build_in(mini);
			else
				ft_out_bin(mini);
		}
	}
	ft_print_tree(mini->first_token, 10);
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
	if (set_signal(&mini))
		return (0);
	ft_get_input(&mini);
	return (0);
}	
