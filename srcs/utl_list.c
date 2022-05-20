/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:30:44 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/11 13:30:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_node(t_ms *mini)
{
	size_t	i;
	t_token	*node;

	i = 0;
	node = mini->first_token;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	ft_inp_append(t_token **lst, t_token *new)
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

t_token	*ft_inp_new(char *cmd, t_ms *mini)
{
	t_token	*rst;

	rst = (t_token *)malloc(sizeof(t_token));
	if (rst == NULL)
		ft_error_free(errno, mini);
	rst->token = cmd;
	rst->type = ft_read_from_node(cmd);
	rst->meta = ft_get_meta_type(rst->type);
	rst->in = TKN_STDIN;
	rst->out = TKN_STDOUT;
	rst->next = NULL;
	rst->args = NULL;
	/*
	if (rst->type == CMD_LITERAL || rst->type == CMD_EXPAND)
	{
		rst->token = ft_strtrim(cmd, "\"\'");
		if (cmd)
			free (cmd);
	}
	*/
	return (rst);
}
