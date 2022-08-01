/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:00:37 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 14:55:05 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_get_files_to_bns(char *file, char *pattern,
		char **to_rst, int scn)
{
	char	*tmp;

	tmp = NULL;
	if (g_mini->status_tkn == 0
		&& (ft_regex(file, pattern) != IS_FALSE || scn == 1))
	{
		*to_rst = ft_strjoin_clean_one(to_rst, " ");
		*to_rst = ft_strjoin_clean_one(to_rst, file);
	}
	else if (g_mini->status_tkn == 1
		&& (ft_regex(file, pattern) != IS_FALSE || scn == 1))
	{
		tmp = ft_strjoin(g_mini->stored, file);
		*to_rst = ft_strjoin_clean_one(to_rst, " ");
		*to_rst = ft_strjoin_clean(to_rst, &tmp, 0);
	}
}

static inline char	*ft_files_to_input(DIR *dir, char *pattern)
{
	struct dirent	*files;
	char			*to_rst;
	char			scn;

	to_rst = NULL;
	scn = 0;
	if (ft_strict_cmp(pattern, "*") == 0
		|| ft_count_char(pattern, '*') == ft_strlen(pattern))
		scn = 1;
	while (1)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (scn == 1 && ft_strncmp(files->d_name, ".", 1) == 0)
			continue ;
		ft_get_files_to_bns(files->d_name, pattern, &to_rst, scn);
	}
	g_mini->status_tkn = 0;
	return (to_rst);
}

static inline void	ft_insert_results(t_ms *mini, char *rst, t_token *node)
{
	char	**hits;
	t_token	*end;
	t_token	*new;
	size_t	i;

	hits = ft_split(rst, ' ');
	if (!hits || !hits[0])
		return ;
	ft_sort_str_tab(hits);
	i = 0;
	end = node->next;
	node->next = NULL;
	ft_safe_free_char(&node->token);
	node->token = ft_strdup(hits[0]);
	node->status = FROM_WILDCARD;
	node->sp_tkn = 1;
	while (hits[++i])
	{
		new = ft_inp_new(ft_strdup(hits[i]), mini);
		new->status = FROM_WILDCARD;
		new->sp_tkn = 1;
		ft_inp_append(&node, new);
	}
	ft_inp_append(&node, end);
	ft_clear_tabs(hits);
}

static inline int	ft_exit_wc(DIR *dir, t_token *node)
{
	ft_safe_free_char(&node->token);
	node->token = ft_strdup(node->stored);
	ft_safe_free_char(&node->stored);
	if (dir == NULL)
		return (ERROR);
	closedir(dir);
	return (ERROR);
}

int	ft_change_wildcard(t_ms *mini, t_token *cmd, t_token *node)
{
	DIR		*dir;
	char	*rst;
	size_t	i;

	i = 0;
	if (node->type == CMD_LITERAL
		|| node->status == FROM_WILDCARD
		|| node->meta == MTA_NULL_TOKEN)
		return (IS_FALSE);
	if (ft_count_char(node->token, '*') == 0)
		return (IS_FALSE);
	dir = opendir(ft_get_bns_path(node, mini));
	if (dir == NULL)
		return (ft_exit_wc(dir, node));
	rst = ft_files_to_input(dir, node->token);
	if (rst == NULL)
		return (ft_exit_wc(dir, node));
	ft_insert_results(mini, rst, node);
	ft_safe_free_char(&rst);
	cmd->status = FROM_WILDCARD;
	g_mini->status_tkn = 0;
	closedir(dir);
	return (IS_TRUE);
}
