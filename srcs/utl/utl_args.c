/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:38:16 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:39:32 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_get_line_argv(t_ms *mini, char *argv[], int i)
{
	char	*rst;
	char	*trimmed;

	rst = NULL;
	trimmed = NULL;
	if (!argv[i])
		ft_error_general(" -c flag without arguments", mini);
	while (argv[i])
	{
		trimmed = ft_strtrim(argv[i], " \n\t");
		if (rst == NULL)
			rst = ft_strtrim(argv[i], " \n\t");
		else
			rst = ft_strjoin_clean_char(&rst, &trimmed, ' ', 1);
		ft_safe_free_char(&trimmed);
		i++;
	}
	mini->line = rst;
}

void	ft_check_for_flags(t_ms *mini, int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc > 1)
		mini->status = 2;
	else
		return ;
	if (ft_strict_cmp(argv[1], "-c") == 0)
		ft_get_line_argv(mini, argv, 2);
	else
		ft_get_line_argv(mini, argv, 1);
}

char	**ft_build_argv(t_ms *mini, t_token *token)
{
	size_t	size;
	size_t	i;
	t_token	*node;
	char	**rst;

	i = 1;
	size = ft_size_branch(mini->first_token->args) + 1;
	rst = (char **)malloc(sizeof(char *) * (size + 1));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst[0] = ft_strdup(token->token);
	rst[size] = NULL;
	node = token->args;
	while (node)
	{
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
