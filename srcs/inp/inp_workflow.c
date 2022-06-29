/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_workflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:33:06 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:15:00 by msoler-e         ###   ########.fr       */
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

static inline void	ft_workflow_rdr(t_token *node, t_token *prev)
{
	if (node->type == RDR_TO_FILE || node->type == RDR_APP_FILE)
	{
		if (prev && prev->meta >= MTA_BUILDIN && prev->meta <= MTA_OUTEXE)
		{
			prev->out = TKN_PIPEOUT;
			node->in = TKN_PIPEIN;
		}
		if (prev && prev->out == TKN_PIPEOUT)
			node->in = TKN_PIPEIN;
		if (node->in && node->next && (node->next->type == RDR_TO_FILE
				|| node->next->type == RDR_APP_FILE))
			node->out = TKN_PIPEOUT;
	}
	else if (node->type == IMP_FROM_FILE || node->type == IMP_HEREDOC)
		node->out = TKN_PIPEOUT;
}

static inline void	ft_workflow_redir(t_ms *mini)
{
	t_token	*node;
	t_token	*prev;

	node = mini->first_token;
	prev = NULL;
	while (node)
	{	
		if (node->meta >= MTA_REDIR_FILE && node->meta <= MTA_REDIR)
		{
			if (node->type == RDR_PIPE)
			{
				if (prev)
					prev->out = TKN_PIPEOUT;
				if (node->next)
					node->next->in = TKN_PIPEIN;
				node = ft_remove_node(node, prev, &mini->first_token);
				continue ;
			}
			else if (node->type == IMP_FROM_FILE || node->type == IMP_HEREDOC
				|| node->type == RDR_TO_FILE || node->type == RDR_APP_FILE)
				ft_workflow_rdr(node, prev);
		}
		prev = node;
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
	ft_print_tree_debug("ft_workflow; antesddeorder-while", mini->first_token);
	ft_workflow_order(mini);
	ft_print_tree_debug("ft_workflow; despues order", mini->first_token);
	ft_check_input_export(mini);
	ft_print_tree_debug("ft_workflow; despues input export", mini->first_token);
	ft_workflow_redir(mini);
	ft_inp_redir(mini);
	ft_print_tree_debug("ft_workflow; despues redirs", mini->first_token);
	ft_workflow_check(mini);
	ft_print_tree_debug("ft_workflow; despues check", mini->first_token);
	return (SUCCESS);
}
