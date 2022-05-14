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

int ft_process_brach(t_ms *mini)
{
	size_t	size;

	size = ft_count_args(mini);
	if (size == 0)
		return (SUCCESS);
	while(size--)
		ft_process_node(mini);
	return (SUCCESS);
}

int ft_delete_node(t_token *node)
{
	if (!node)
		return (ERROR);
	if (node->token)
		free (node->token);
	node->next = NULL;
	node->args = NULL;
	free (node);
	return (SUCCESS);
}

int ft_process_node(t_ms *mini)
{
	t_token	*node;

	if (!mini->first_token)
		return (SUCCESS);
	node = mini->first_token;
	mini->first_token = node->next;
	free (node->token);
	node->next = NULL;
	free (node);
	return (SUCCESS);
}

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
	return (rst);
}
