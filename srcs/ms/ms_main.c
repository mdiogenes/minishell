/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:34 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:41:56 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_process_inputs(t_ms *mini)
{
	if (mini->first_token == NULL)
		return (ERROR);
	while (mini->first_token)
		ft_token_dir(mini);
	ft_clear_nodes(&mini->first_token, &mini->last_token);
	return (SUCCESS);
}

static inline int	ft_parser_process(t_ms *mini)
{
	if (ft_parse(mini) == ERROR)
	{
		ft_clear_nodes(&mini->first_token, &mini->last_token);
		return (ERROR);
	}
	if (mini->first_token == NULL)
		return (ERROR);
	mini->process = 0;
	ft_process_inputs(mini);
	return (mini->exitstatus);
}

static inline int	ft_get_input(t_ms *mini)
{
	while (mini->status > 0)
	{
		set_signal();
		mini->pid_child = 0;
		if (mini->status != 2)
		{
			ft_get_path_prompt(mini);
			ft_safe_free_char(&mini->line);
			mini->line = readline(mini->prompt);
		}
		if (!mini->line)
			signal_ctrld(mini);
		if (mini->line)
			ft_parser_process(mini);
		if (mini->status == 2)
			break ;
	}
	return (SUCCESS);
}

static inline void	ft_upd_envar(t_ms *mini)
{
	ft_safe_free_char(&mini->stored);
	mini->stored = ft_is_bin_exe("env", mini, NULL);
	ft_export_var("_", mini->stored, 0, mini);
	ft_safe_free_char(&mini->stored);
}

int	main(int argc, char *argv[], char **envp)
{
	t_ms	mini;
	t_token	*home;

	mini_getpid(&mini, 0);
	g_mini = &mini;
	if (ft_init_minishell(&mini) == ERROR)
		ft_error_general("Init error: main struct could not be init", &mini);
	ft_check_for_flags(&mini, argc, argv);
	if (ft_env_to_list(envp, &mini) == ERROR)
		ft_error_general("Init error:env variables couldn't be loaded", &mini);
	home = ft_find_envar_export("HOME", &mini);
	if (home)
		mini.homecons = ft_strdup(home->args->token);
	else
		ft_error_general("Init error:env variables couldn't be loaded", &mini);
	if (ft_get_bin_paths(&mini) == ERROR)
		ft_error_general("Init error: bin paths could not be loaded", &mini);
	ft_upd_envar(&mini);
	ft_get_input(&mini);
	ft_free_exit(&mini);
	g_mini = NULL;
	exit (mini.exitstatus);
}	
