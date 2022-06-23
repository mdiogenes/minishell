/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:38:16 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 10:54:44 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_line_argv(t_ms *mini, char *argv[])
{
	char	*rst;
	int		i;

	rst = NULL;
	if (ft_strict_cmp(argv[1], "-c") == 0)
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		if (rst == NULL)
			rst = ft_strtrim(argv[i], " \n\t");
		else
			rst = ft_strjoin_clean_char(rst,
					ft_strtrim(argv[i], " \n\t"), ' ', 0);
		i++;
	}
	mini->line = rst;
}

char	**ft_get_rst_argv(t_ms *mini)
{
	size_t	size;
	char	**rst;

	size = ft_size_branch(mini->first_token->args) + 1;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	return (rst);
}

char	**ft_build_argv(t_ms *mini, t_token *token)
{
	size_t	i;
	t_token	*node;
	char	**rst;

	rst = ft_get_rst_argv(mini);
	i = 1;
	rst[0] = ft_strdup(token->token);
	node = token->args;
	while (node)
	{
		if (token->status == FROM_EXPAND)
			rst[i] = ft_strjoin(mini->path, token->token);
		else
			rst[i] = ft_strdup(node->token);
		node = node->next;
		i++;
	}
	return (rst);
}

char	**ft_build_arenv(t_ms *mini)
{
	int		size;
	size_t	i;
	t_token	*node;
	char	**rst;

	size = ft_size_branch(mini->env);
	i = 0;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[size] = NULL;
	node = mini->env;
	while (node)
	{
		if (node->args == NULL)
			rst[i] = ft_strdup(node->token);
		else
			rst[i] = ft_strjoin_char(node->token, node->args->token, '=');
		node = node->next;
		i++;
	}
	return (rst);
}

int	ft_delete_args(t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_delete_node(node));
	if (node->args && node->next)
		return (ft_delete_args(node->args)
			+ ft_delete_args(node->next)
			+ ft_delete_node(node));
	if (!node->args && node->next)
		return (ft_delete_args(node->next)
			+ ft_delete_node(node));
	return (ft_delete_args(node->args)
		+ ft_delete_node(node));
}
