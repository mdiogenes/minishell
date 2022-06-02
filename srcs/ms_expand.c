/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/01 14:27:57 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_var(char **dst, int *i_j, char **str, t_ms *mini)
{
	t_token	*node;
	char	*var;
	int		*i;
	int		*j;

	i = &i_j[0];
	j = &i_j[1];
	node = NULL;
	var = NULL;
	dst = join_str(dst, str, *j, *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*str)[*i] != ' ' && (*i < (int)ft_strlen(*str))
		&& (*str)[*i] != '$')
		*i = *i + 1;
	node = ft_find_envar_export(ft_substr((*str), *j, *i - *j), mini);
	if (!node)
		var = NULL;
	else if (node->args->token)
		var = node->args->token;
	if (var)
		*dst = ft_strjoin(*dst, var);
	else
		*dst = ft_strjoin(*dst, "\0");
	*j = *i;
}

void	ft_caseinterr(char *str, char **dst, int *ptri, int *ptrj)
{
	int	i;
	int	j;

	i = *ptri;
	j = *ptrj;
	if ((str[i] == '$') && (str[i + 1] == '?'))
	{
		if (!*dst)
		{
			*dst = ft_substr(str, j, i - j);
			*dst = ft_strjoin(*dst, "lastpid");
		}
		else
		{
			*dst = ft_strjoin(*dst, ft_substr(str, j, i - j));
			*dst = ft_strjoin(*dst, "lastpid");
		}
		i ++;
		j = i + 1;
	}
	*ptri = i;
	*ptrj = j;
}

void	rarecase(char *str, char **dst, int *ptri, int *ptrj)
{
	int	i;
	int	j;
	int	len;

	i = *ptri;
	j = *ptrj;
	len = ft_strlen(str);
	if (i + 1 < len)
	{
		if ((str[i] == '$') && (str[i + 1] == '$'))
		{
			*dst = *join_str(dst, &str, j, i ++ - j + 2);
			j = i ++ + 1;
		}
		if (((str[i] == '$') && (str[i + 1] == ' '))
			|| ((str[i] == '$') && (i + 1 == len)))
		{
			*dst = *join_str(dst, &str, j, i - j + 2);
			j = i + 1;
		}
		ft_caseinterr(str, dst, &i, &j);
	}
	*ptri = i;
	*ptrj = j;
}

int	ft_expand_node(t_ms *mini, t_token *node)
{
	char	*dst;
	int		i_j[2];

	i_j[0] = 0;
	i_j[1] = 0;
	dst = NULL;
	while (i_j[0] < (int)ft_strlen(node->token))
	{
		if ((node->token[i_j[0]] == '$') && (node->token[i_j[0] +1] != '?')
			&& (i_j[0] + 1 < (int)ft_strlen(node->token))
			&& (node->token[i_j[0] + 1] != '$')
			&& (node->token[i_j[0] + 1] != ' '))
			ft_change_var(&dst, &i_j[0], &node->token, mini);
		rarecase(node->token, &dst, &i_j[0], &i_j[1]);
		if (node->token[i_j[0]] != '$' || !node->token[i_j[0] + 1])
			i_j[0]++;
	}	
	if (i_j[0] > i_j[1])
		dst = *join_str(&dst, &node->token, i_j[1], i_j[0] - i_j[1]);
	if (node->token)
		free(node->token);
	node->token = dst;
	return (SUCCESS);
}

int	ft_get_expand(t_ms *mini, t_token *node)
{
	if (!node)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_expand_node(mini, node));
	if (node->args && node->next)
		return (ft_get_expand(mini, node->args)
			+ ft_get_expand(mini, node->next)
			+ ft_expand_node(mini, node));
	if (!node->args && node->next)
		return (ft_get_expand(mini, node->next)
			+ ft_expand_node(mini, node));
	return (ft_get_expand(mini, node->args)
		+ ft_expand_node(mini, node));
}
