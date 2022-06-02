/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:09:07 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 09:41:41 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr_exp(const char *haystack, const char *needle, size_t loc, size_t *rst)
{
	size_t	k;
	size_t	len_needle;
	char	*sheaf;

	*(rst) = 0;
	if (haystack == needle)
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	sheaf = (char *)haystack;
	if (len_needle == 0)
		return (sheaf);
	while (sheaf[*(rst)] && *(rst) < loc)
	{
		if (sheaf[*(rst)] == needle[0])
		{
			k = 0;
			while (sheaf[*(rst) + k] && sheaf[*(rst) + k] == needle[k] && *(rst) + k < loc)
				k++;
			if (k == len_needle)
				return (&sheaf[*(rst)]);
		}
		*(rst) = *(rst) + 1;
	}
	*(rst) = 0;
	return (NULL);
}


int ft_compare_sort(char *s1, char *s2)
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
	t_token *prev;
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

int ft_print_vars(t_ms *mini)
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
		printf("%s", node->token);
		if (node->args)
			printf("=\"%s\"", node->args->token);
		printf("\n");
		node = node->next;
	}
	ft_process_branch(mini);
	return (SUCCESS);
}

int	ft_find_envar_expand(t_token *token, t_ms *mini)
{
	t_token	*env;
	char	*exp;
	char	*tmp;
	size_t	rst;
	size_t	len_tkn;
	size_t	len_var;

	if (token->type > CMD_ENV_VAR)
		return (SUCCESS);
	env = mini->env;
	while (env)
	{
		len_tkn = ft_strlen(token->token);
		tmp = ft_strnstr_exp(token->token, env->token, len_tkn, &rst);
		if (rst > 0 && token->token[rst - 1] == '$')
		{
			//if (ft_strlenchar(tmp, ' ') != ft_strlen(env->token))
			//	printf("hola\n");
			tmp = ft_strdup(token->token);
			if (env->args)
				len_var = ft_strlen(env->args->token);
			else
				len_var = 0;
			if (env->args)
				exp = ft_strnjoin(token->token, env->args->token, rst - 1, len_var);
			else
				exp = ft_strndup(token->token, rst - 1);
		
			free(token->token);
			token->token = ft_strjoin(exp, &tmp[rst + ft_strlen(env->token)]);
			free(tmp);
			free(exp);
		}
		if (rst == 0)
			env = env->next;
	}
	return (SUCCESS);
}

int	ft_expand_envar(t_token *node, t_ms *mini)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
	{
		return (ft_find_envar_expand(node, mini));
	}
	if (node->args && node->next)
		return (ft_expand_envar(node->args, mini)
			+ ft_expand_envar(node->next, mini)
			+ ft_find_envar_expand(node, mini));
	if (!node->args && node->next)
		return (ft_expand_envar(node->next, mini)
			+ ft_find_envar_expand(node, mini));
	if (node->args && !node->next)
		return (ft_expand_envar(node->args, mini)
			+ ft_find_envar_expand(node, mini));
	return (0);
}
