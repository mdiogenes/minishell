#include "minishell.h"

void	ft_print_tree(t_token *node, int space)
{
	int i;

	space += COUNT;
	i = COUNT - 1;
    if (node == NULL)
        return;
    ft_print_tree(node->next, space);
    printf("\n");
    while (i++ < space)
        printf(" ");
    printf("%s (%d in - %d out)[%d t - %d m]", node->token, node->in, node->out, node->type, node->meta);
    ft_print_tree(node->args, space);
}