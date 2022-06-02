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
    printf("%s (%d in - %d out)[%d t - %d m (len %zu)]", node->token, node->in, node->out, node->type, node->meta, ft_strlen(node->token));
    ft_print_tree(node->args, space);
}

void    ft_print_argv(char *argv[])
{
    int i;

    if (argv == NULL)
        return;
    i = 0;
    while (argv[i])
    {
        printf("%d - %s\n", i, argv[i]);
        i++;
    }
    printf("\n");
}