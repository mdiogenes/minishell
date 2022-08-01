/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:46:04 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/19 09:46:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_remove_chars(char *s, char c)
{
	size_t	newlen;
	char	*rst;
	int		o_c[2];

	newlen = ft_strlen(s) - ft_count_char(s, c);
	if (newlen <= 0)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (newlen + 1));
	if (rst == NULL)
		ft_error_free(errno, g_mini);
	rst[newlen] = '\0';
	ft_init_vector(&o_c[0], 0, 2);
	while (s[o_c[0]])
	{
		if (s[o_c[0]] == c)
			o_c[0]++;
		else
		{
			rst[o_c[1]] = s[o_c[0]];
			o_c[1]++;
			o_c[0]++;
		}
	}
	return (rst);
}

t_token	*ft_check_chars(t_token *node,
		t_token *prev, t_ms *mini)
{
	char	*tmp;

	if (ft_count_char(node->token, '\\') > 0)
	{
		tmp = ft_remove_chars(node->token, '\\');
		if (tmp == NULL)
			return (ft_remove_node(node, prev, &mini->first_token));
		ft_safe_free_char(&node->token);
		node->token = tmp;
		return (node);
	}
	return (NULL);
}

int	ft_clean_vars(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;
	t_token	*evl;

	if (!mini || !mini->first_token)
		return (ERROR);
	node = mini->first_token;
	prev = NULL;
	evl = NULL;
	while (node)
	{
		if (node->type != CMD_LITERAL && node->type != CMD_EXPAND)
			evl = ft_check_chars(node, prev, mini);
		if (evl != NULL)
		{
			node = evl;
			evl = NULL;
			continue ;
		}
		evl = NULL;
		prev = node;
		node = node->next;
	}
	return (SUCCESS);
}
