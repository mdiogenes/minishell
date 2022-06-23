/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_envars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:09:07 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/16 14:55:35 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compare_sort(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	n;
	int		cmp;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 > len_s2)
		n = len_s1;
	else if (len_s1 < len_s2)
		n = len_s2;
	else
		n = len_s1;
	cmp = ft_strncmp(s1, s2, n);
	if (cmp == 0)
		return ((int)n);
	else
		return (cmp);
}

void	ft_env_sort(t_token **first_env, t_token *new)
{
	t_token	*prev;
	t_token	*node;

	node = *first_env;
	prev = NULL;
	if (node == NULL)
	{
		*first_env = new;
		return ;
	}
	while (node)
	{
		if (ft_compare_sort(node->token, new->token) > 0)
		{
			new->next = node;
			if (prev == NULL)
				*first_env = new;
			else
				prev->next = new;
			return ;
		}
		prev = node;
		node = node->next;
	}
	prev->next = new;
}

int	ft_print_vars(t_ms *mini)
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
		printf("declare -x %s", node->token);
		if (node->args)
		{
			if (ft_strict_cmp(node->args->token, "\"\"") == 0)
				printf("=\"\"");
			else
				printf("=\"%s\"", node->args->token);
		}
		printf("\n");
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}
