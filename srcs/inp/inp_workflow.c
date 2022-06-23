/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_workflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:33:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:48:23 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_workflow_params(t_token *node)
{
	t_token	*args;

	if (node->next->meta > MTA_ARGS)
		return ;
	args = node->next;
	while (args)
	{
		if (args->next && args->next->meta > MTA_ARGS)
			break ;
		args = args->next;
	}
	if (args)
	{
		node->next = args->next;
		args->next = NULL;
	}
	else
		node->next = NULL;
}

static inline int	ft_workflow_clean(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	if (tmp->meta >= MTA_REDIR_FILE && tmp->meta <= MTA_REDIR)
	{
		node->out = TKN_PIPEOUT;
		if (tmp->type == RDR_PIPE)
		{
			node->next = tmp->next;
			ft_delete_node(tmp);
		}
		return (TKN_PIPEIN);
	}
	else if (tmp->type == NEXT_CMD)
	{
		if (tmp->next)
			node->next = tmp->next;
		else
			node->next = NULL;
		ft_delete_node(tmp);
		return (TKN_STDIN);
	}
	return (TKN_STDIN);
}

static inline void	ft_workflow_redir(t_ms *mini)
{
	t_token	*node;
	char	in;

	in = TKN_STDIN;
	node = mini->first_token;
	while (node)
	{	
		if (node->in != in)
			node->in = in;
		if (node->type >= IMP_FROM_FILE && node->type <= IMP_HEREDOC)
		{
			node->out = TKN_PIPEOUT;
			in = TKN_PIPEIN;
		}
		else if (node->next && node->next->meta >= MTA_REDIR_FILE
			&& node->next->meta <= MTA_REDIR)
			in = ft_workflow_clean(node);
		else if (node->next && node->next->type == NEXT_CMD)
			in = ft_workflow_clean(node);
		else
			in = TKN_STDIN;
		node = node->next;
	}
}

static inline void	ft_workflow_order(t_ms *mini)
{
	t_token	*prev;
	t_token	*aux;
	t_token	*node;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{
		if (node->next && (node->next->type == IMP_FROM_FILE
				|| node->next->type == IMP_HEREDOC))
		{
			if (prev != NULL)
				prev->next = node->next;
			else
				mini->first_token = node->next;
			aux = node->next->next;
			node->next->next = node;
			node->next = aux;
		}
		prev = node;
		node = node->next;
	}
}

int	ft_workflow(t_ms *mini)
{
	t_token	*node;

	if (ft_input_preprocess(mini) == ERROR)
		return (ERROR);
	ft_print_tree_debug("ft_workflow despues preproceso", mini->first_token);
	ft_clean_quotes(mini);
	ft_print_tree_debug("ft_workflow despues quotes", mini->first_token);
	node = mini->first_token;
	if (!node)
		return (ERROR);
	while (node)
	{
		if (node->next && node->next->meta <= MTA_ARGS)
		{
			node->args = node->next;
			ft_workflow_params(node);
		}
		node = node->next;
	}
	ft_workflow_order(mini);
	ft_print_tree_debug("ft_workflow; despues order", mini->first_token);
	//ft_workflow_check(mini);
	//ft_print_tree_debug("ft_workflow; despues check", mini->first_token);
	ft_check_input_export(mini);
	ft_print_tree_debug("ft_workflow; despues input export", mini->first_token);
	ft_workflow_redir(mini);
	return (SUCCESS);
}
