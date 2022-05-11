/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:54:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/10 20:54:46 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*ft_strdup_input(char *src, size_t len, t_ms *mini)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		ft_error_free(errno, mini);
	dst[len] = '\0';
	while (len-- > 0)
		dst[len] = src[len];
	return (dst);
}

static inline size_t	ft_strlen_to(const char *s, int scn)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != ' ' && ft_is_reserved(s[i]) == (1 * scn))
		i++;
	return (i);
}

static inline void	ft_inp_append(t_token **lst, t_token *new)
{
	t_token	*node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

static inline t_token	*ft_inp_new(char *cmd, t_ms *mini)
{
	t_token	*rst;

	rst = (t_token *)malloc(sizeof(t_token));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst->token = cmd;
	rst->type = ft_read_from_node(cmd);
	rst->next = NULL;
	return (rst);
}

int	ft_load_input(t_ms *mini)
{
	char		*tmp;
	size_t		i;
	t_token		*node;
	size_t		len;

	i = 0;
	while (mini->line[i])
	{
		if (mini->line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (ft_is_reserved(mini->line[i]) == 1)
			len = ft_strlen_to(&mini->line[i], 1);
		else
			len = ft_strlen_to(&mini->line[i], 0);
		tmp = ft_strdup_input(&mini->line[i], len, mini);
		node = ft_inp_new(tmp, mini);
		ft_inp_append(&mini->first_token, node);
		mini->num_tokens++;
		i = i + len;
	}
	return (1);
}
