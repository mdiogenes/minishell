/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:56:30 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/22 13:46:33 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_env(char *token, t_ms *mini)
{
	t_token	*rst;

	rst = (t_token *)malloc(sizeof(t_token));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst->token = token;
	rst->type = 0;
	rst->meta = 0;
	rst->in = 0;
	rst->out = 0;
	rst->next = NULL;
	rst->args = NULL;
	return (rst);
}

t_token	*ft_find_envar_export(char *needle, t_ms *mini)
{
	t_token	*node;
	size_t	len;

	node = mini->env;
	while (node)
	{
		len = ft_strlen(node->token);
		if (len == ft_strlen(needle)
			&& ft_strncmp(node->token, needle, len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	ft_export_var(char *var, char *val, t_ms *mini)
{
	t_token	*new;
	t_token	*dst;

	dst = ft_find_envar_export(var, mini);
	if (dst == NULL)
	{
		new = ft_new_env(ft_strdup(var), mini);
		if (val != NULL)
			new->args = ft_new_env(ft_strdup(val), mini);
		ft_env_sort(&mini->env, new);
	}
	else
	{
		if (val == NULL)
			return ;
		ft_delete_node(dst->args);
		dst->args = ft_new_env(ft_strdup(val), mini);
	}
}

int	ft_export_cmd(t_ms *mini)
{
	t_token	*token;
	char	*value;

	if (!mini->first_token->args)
		return (ft_print_vars(mini));
	token = mini->first_token->args;
	while (token)
	{
		if (token->args)
			value = token->args->token;
		else
			value = NULL;
		ft_export_var(token->token, value, mini);
		token = token->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
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
			new = ft_new_env(ft_strdup(env[i]), mini);
		else
		{
			var = ft_split(env[i], '=');
			new = ft_new_env(var[0], mini);
			new->type = SYS_VAR;
			if (ft_strict_cmp(new->token, "OLDPWD") != 0)
				new->args = ft_new_env(var[1], mini);
			free (var);
		}
		ft_env_sort(&mini->env, new);
		i++;
	}
	return (SUCCESS);
}
