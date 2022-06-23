/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaa_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:55:35 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/23 10:42:30 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tree(t_token *node, int space, char *icon)
{
	int	i;

	space += COUNT;
	i = COUNT - 1;
	if (node == NULL)
		return ;
	ft_print_tree(node->next, space, "->");
	printf("\n");
	while (i++ < space)
		printf(" ");
	printf("%s %s [%p node] [%p token](%d in - %d out)[%d t - %d m (len %zu)]",icon, node->token, node, node->token, node->in,node->out, node->type,
		node->meta, ft_strlen(node->token));
	ft_print_tree(node->args, space, "L->");
}

void ft_print_list(char *function, t_token *node)
{
	t_token *token;

	if (DEBUG == 0)
		return ;
	token = node;
	(void)token;
	printf("\n ==== %s ====\n", function);
	while(node)
	{
		printf("%s -> ", node->token);
			if (node->args)
				printf(" %s ", node->args->token);
			else
				printf(" NULL ");
		printf("\n");
	}
	printf("\n ==== END %s ====\n", function);
}

void	ft_print_tree_debug(char *function, t_token *node)
{
	if (DEBUG == 0)
		return ;
	printf("\n ==== %s ====\n", function);
	ft_print_tree(node, 10, "=>>");
	printf("\n ==== END %s ====\n", function);
}

void	ft_print_argv(char *argv[])
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		printf("%d - %s\n", i, argv[i]);
		i++;
	}
	printf("\n");
}

void	ft_test(t_ms *mini)
{
	t_token	*node;

	node = mini->first_token;
	while (node)
	{
		printf("%s %d\n", node->token, node->type);
		node = node->next;
	}
}
