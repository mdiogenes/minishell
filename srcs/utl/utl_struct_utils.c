/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:23:45 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/22 11:48:00 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_ms *mini)
{
	if (mini->line)
		free (mini->line);
	if (mini->path)
		free (mini->path);
	if (mini->homecons)
		free (mini->homecons);
	if (mini->prompt)
		free (mini->prompt);
	if (mini->first_token)
		ft_clear_nodes(mini);
	if (mini->bin_paths)
		ft_clear_tabs(mini->bin_paths);
}

void	ft_get_path_prompt(t_ms *mini)
{
	char	pwd[PATH_MAX];
	char	*tmp;

	if (mini->path)
		free (mini->path);
	mini->path = ft_strdup(getcwd(pwd, PATH_MAX));
	mini->path = ft_strjoin_clean(mini->path, "/", 1);
	if (mini->prompt)
		free (mini->prompt);
	tmp = ft_strjoin("\e[33m[42-ms ", ft_strrchr(getcwd(pwd, PATH_MAX), '/'));
	tmp = ft_strjoin_clean(tmp, "] [", 1);
	tmp = ft_strjoin_clean(tmp, ft_itoa(mini->exitstatus), 0);
	mini->prompt = ft_strjoin(tmp, "]\e[0m ");
	free (tmp);
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
	mini->exitstatus = 0;
	mini->status = 1;
	mini->pid = 0;
	mini->first_token = NULL;
	mini->line = NULL;
	mini->path = NULL;
	mini->homecons = NULL;
	mini->prompt = NULL;
	mini->env = NULL;
	//mini->hello = ft_sayhello;
	//mini->bin_paths = NULL;
	ft_get_path_prompt(mini);
	return (SUCCESS);
}
