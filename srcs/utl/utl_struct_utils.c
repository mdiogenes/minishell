/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:23:45 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:24:46 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_exit(t_ms *mini)
{
	ft_free_pipes(mini);
	ft_safe_free_char(&mini->homecons);
	ft_safe_free_char(&mini->line);
	ft_safe_free_char(&mini->stored);
	ft_safe_free_char(&mini->prompt);
	ft_clear_nodes(&mini->first_token, NULL);
	mini->last_token = NULL;
	ft_clear_nodes(&mini->env, NULL);
	if (mini->bin_paths)
		ft_clear_tabs(mini->bin_paths);
	rl_clear_history();
	return (mini->exitstatus);
}

void	ft_get_path_prompt(t_ms *mini)
{
	char	pwd[PATH_MAX];
	char	*tmp;
	char	*path_now;

	path_now = getcwd(pwd, PATH_MAX);
	if (path_now == NULL)
		path_now = ft_strdup(mini->path);
	else
	{
		path_now = ft_strdup(getcwd(pwd, PATH_MAX));
		ft_safe_free_char(&mini->path);
		mini->path = ft_strdup(path_now);
	}
	ft_safe_free_char(&mini->prompt);
	ft_safe_free_char(&g_mini->stored);
	mini->stored = ft_itoa(mini->exitstatus);
	tmp = ft_strjoin("\e[33m[42-ms ", ft_strrchr(path_now, '/'));
	tmp = ft_strjoin_clean_one(&tmp, "] [");
	tmp = ft_strjoin_clean(&tmp, &mini->stored, 0);
	mini->prompt = ft_strjoin(tmp, "]\e[0m ");
	ft_safe_free_char(&tmp);
	ft_safe_free_char(&path_now);
}

int	ft_get_bin_paths(t_ms *mini)
{
	t_token		*path;

	path = ft_find_envar_export("PATH", mini);
	mini->bin_paths = ft_split(path->args->token, ':');
	return (SUCCESS);
}

int	ft_init_minishell(t_ms *mini)
{
	mini->pipes = NULL;
	mini->status = 1;
	mini->exitstatus = 0;
	mini->process = 0;
	mini->pid_child = 0;
	mini->status_tkn = 0;
	mini->sp_tkn = 0;
	mini->homecons = NULL;
	mini->line = NULL;
	mini->stored = NULL;
	mini->prompt = NULL;
	mini->path = NULL;
	mini->first_token = NULL;
	mini->last_token = NULL;
	mini->env = NULL;
	mini->bin_paths = NULL;
	ft_get_path_prompt(mini);
	return (SUCCESS);
}

void	ft_join_nodes(t_token **head, t_token *start, t_token *end)
{
	t_token	*node;
	t_token	*prev;

	if (start == NULL || start == end)
		return ;
	node = start;
	if (*head == start)
		prev = NULL;
	else
	{
		prev = *head;
		while (prev->next != start)
			prev = prev->next;
	}
	while (node && node->next)
	{
		node->next->token = ft_strjoin_clean(&node->token,
				&node->next->token, 0);
		node = ft_remove_node(node, prev, head);
	}
}
