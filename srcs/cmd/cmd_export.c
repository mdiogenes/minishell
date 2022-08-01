/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:29:28 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:20:07 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_print_vars(t_ms *mini)
{
	t_token	*node;

	node = mini->env;
	while (node)
	{
		if (node->type == SYS_HIDDEN)
		{
			node = node->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(node->token, STDOUT_FILENO);
		if (node->args)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(node->args->token, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}

static inline char	**ft_build_data(void)
{
	char	**rst;

	rst = (char **)malloc(sizeof(char *) * 3);
	if (!rst)
		ft_error_free(errno, g_mini);
	rst[2] = NULL;
	rst[1] = NULL;
	return (rst);
}

static inline void	ft_fixed_dup(char **tab, t_token *node)
{
	char	*tmp;

	if (ft_count_tab(tab) == 1 && ft_last_char(tab[0]) == '=')
	{
		tmp = tab[0];
		tab[0] = ft_strndup(tab[0], ft_strlenchar(tab[0], '='));
		tab[1] = ft_strdup("\0");
		ft_safe_free_char(&tmp);
	}
	if (ft_last_char(tab[0]) == '+')
	{
		node->exp_sts = 1;
		tmp = tab[0];
		tab[0] = ft_strndup(tab[0], ft_strlenchar(tab[0], '+'));
		ft_safe_free_char(&tmp);
	}
}

static inline char	**ft_get_data(char *token, t_token *node)
{
	char	**vartab;
	size_t	len;
	char	**rst;

	rst = ft_build_data();
	vartab = ft_split(token, '=');
	len = ft_count_tab(vartab);
	if (len <= 1)
		rst[0] = ft_strdup(token);
	else if (len == 2 && ft_count_char(token, '=') == 1)
	{
		rst[0] = ft_strdup(vartab[0]);
		rst[1] = ft_strdup(vartab[1]);
	}
	else
	{
		len = ft_strlenchar(token, '=');
		rst[0] = ft_strndup(token, len);
		rst[1] = ft_strdup(&token[len + 1]);
	}
	ft_clear_tabs(vartab);
	ft_fixed_dup(rst, node);
	return (rst);
}

int	ft_export_cmd(t_ms *mini)
{
	t_token	*token;
	char	**data;

	if (!mini->first_token->args)
		return (ft_print_vars(mini));
	token = mini->first_token->args;
	while (token)
	{
		data = ft_get_data(token->token, token);
		if (ft_check_var_name(data[0]) == IS_FALSE)
			ft_export_id_error(mini, token);
		else
			ft_export_var(data[0], data[1], token->exp_sts, mini);
		ft_clear_tabs(data);
		token = token->next;
	}
	ft_process_branch(mini);
	return (mini->exitstatus);
}
