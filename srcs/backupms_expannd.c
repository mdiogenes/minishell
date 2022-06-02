/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/01 12:40:56 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_var(char **dst, int *i_j, int i, int j, char **str, t_ms *mini)
{
	t_token	*node;
	char	*var;

	i_j[1] = 5;
	printf("\ni_j%d\n",i_j[0]);
	node = NULL;
	var = NULL;
	dst = join_str(dst, str, j, i - j);
	i ++;
	j = i;
	while ((*str)[i] != ' ' && (i < (int)ft_strlen(*str)) && (*str)[i] != '$')
		i++;
	node = ft_find_envar_export(ft_substr((*str), j, i -j), mini);
	if (!node)
		var = NULL;
	else if (node->args->token)
		var = node->args->token;
	if (var)
		*dst = ft_strjoin(*dst, var);
	else
		*dst = ft_strjoin(*dst, "\0");
	return (i);
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
	char	*str;
	int		len;
	int		i;
	int		j;
	int		*i_j;

	i_j = (int *)malloc(sizeof (int)*2);	
	str = node->token;
	len = ft_strlen(str);
	i_j[0]=1;
	i_j[1]=2;

	i = 0;
	j = 0;
	dst = NULL;
	while (i < len)
	{
		if ((str[i] == '$') && (i + 1 < len) && (str[i + 1] != '$')
			&& (str[i + 1] != ' ') && (str[i +1] != '?'))
		{
			i = ft_change_var(&dst, i_j, i, j, &str, mini);
			j = i;
		}
		rarecase(str, &dst, &i, &j);
		if (str[i] != '$' || !str[i + 1])
			i++;
	}	
	if (i > j)
		dst = *join_str(&dst, &str, j, i - j);
	if (str)
		free(str);
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
