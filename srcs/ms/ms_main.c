/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:34:59 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_process_inputs(t_ms *mini)
{
	if (mini->first_token == NULL)
		return (ERROR);
	while (mini->first_token)
		ft_token_dir(mini);
	ft_clear_nodes(mini);
	return (SUCCESS);
}

static inline int	ft_parser_process(t_ms *mini)
{
	if (ft_parse(mini) == ERROR)
	{
		ft_clear_nodes(mini);
		return (ERROR);
	}
	if (mini->first_token == NULL)
		return (ERROR);
	ft_print_tree_debug("main", mini->first_token);
	ft_process_inputs(mini);
	return (mini->exitstatus);
}

static inline int	ft_get_input(t_ms *mini, int argc, char *argv[])
{
	using_history();
	while (mini->status == 1)
	{
		ft_get_path_prompt(mini);
		if (mini->line)
			free(mini->line);
		if (argc > 2)
			ft_get_line_argv(mini, argv);
		else
			mini->line = readline(mini->prompt);
		if (!mini->line)
			signal_ctrld(mini);
		if (mini->line && *mini->line)
		{
			add_history(mini->line);
			ft_parser_process(mini);
		}
		if (argc >= 3)
			mini->status = 0;
	}
	return (mini->exitstatus);
}

int	main(int argc, char *argv[], char **envp)
{
	t_ms	mini;
	t_token	*home;

	if (ft_init_minishell(&mini) == ERROR)
		ft_error_general("error inicializar variables", &mini);
	if (ft_env_to_list(envp, &mini) == ERROR)
		ft_error_general("error copia envp", &mini);
	mini_getpid(&mini);
	home = ft_find_envar_export("HOME", &mini);
	g_mini = &mini;
	if (home)
		mini.homecons = ft_strdup(home->args->token);
	else
		ft_error_general("error copia variable HOME", &mini);
	if (ft_get_bin_paths(&mini) == ERROR)
		ft_error_general("error obtencion PATH", &mini);
	if (set_signal(&mini) == ERROR)
		return (ERROR);
	ft_get_input(&mini, argc, argv);
	return (mini.exitstatus);
}	
