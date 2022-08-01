/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:56:30 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/28 14:18:08 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_find_envar_export(char *needle, t_ms *mini)
{
	t_token	*node;

	node = mini->env;
	while (node)
	{
		if (ft_strict_cmp(node->token, needle) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

static inline void	ft_join_to_var(t_token *dst, char *val,
		unsigned char sts, t_ms *mini)
{
	if (val == NULL)
		return ;
	if (!dst->args)
		dst->args = ft_inp_new(ft_strdup(val), mini);
	else if (dst->args && sts == 0)
	{
		ft_delete_node(dst->args);
		dst->args = ft_inp_new(ft_strdup(val), mini);
	}
	else if (dst->args && sts == 1)
		dst->args->token = ft_strjoin_clean(&dst->args->token, &val, 1);
}

void	ft_export_var(char *var, char *val, unsigned char sts, t_ms *mini)
{
	t_token	*new;
	t_token	*dst;

	dst = ft_find_envar_export(var, mini);
	if (dst == NULL)
	{
		new = ft_inp_new(ft_strdup(var), mini);
		if (val != NULL)
			new->args = ft_inp_new(ft_strdup(val), mini);
		ft_env_sort(&mini->env, new);
	}
	else
		ft_join_to_var(dst, val, sts, mini);
	if (ft_strict_cmp(var, "PATH") == 0)
	{
		ft_clear_tabs(mini->bin_paths);
		mini->bin_paths = ft_split(val, ':');
	}
}

int	ft_env_to_list(char **env, t_ms *mini)
{
	char	**var;
	t_token	*new;
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strrchr(env[i], '=') == NULL)
			new = ft_inp_new(ft_strdup(env[i]), mini);
		else
		{
			var = ft_split(env[i], '=');
			new = ft_inp_new(ft_strdup(var[0]), mini);
			new->type = SYS_VAR;
			if (ft_strict_cmp(new->token, "OLDPWD") != 0)
				new->args = ft_inp_new(ft_strdup(var[1]), mini);
			ft_clear_tabs(var);
		}
		ft_env_sort(&mini->env, new);
		i++;
	}
	ft_shlvl_check(mini);
	ft_export_var("OLDPWD", NULL, 0, mini);
	return (SUCCESS);
}
