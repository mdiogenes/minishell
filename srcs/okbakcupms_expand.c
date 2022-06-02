/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/01 10:45:11 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_var(char **dst, int i, int j, char **str)
{
	char	*var;
	char	*proba;

	var = NULL;
	dst = join_str(dst, str, j, i - j);
	i ++;
	j = i;
	while ((*str)[i] != ' ' && (i < (int)ft_strlen(*str)) && (*str)[i] != '$')
	i++;
	proba = ft_substr(*str, j, i - j);
	var = getenv((const char *)proba);
	free (proba);
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

char	*ft_expand(char *str, int len)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dst = NULL;
	while (i < len)
	{
		if ((str[i] == '$') && (i + 1 < len) && (str[i + 1] != '$')
			&& (str[i + 1] != ' ') && (str[i +1] != '?'))
		{
			i = ft_change_var(&dst, i, j, &str);
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
	return (dst);
}

void	ft_get_expand(t_ms	*mini)
{
	t_token	*token;
	t_token	*args;
	int		len;

	token = mini->first_token;
	args = mini->first_token->args;
	len = 0;
	while (token)
	{
		while (args)
		{	
			if (args->type == CMD_EXPAND || args->type == NO_TYPE
				|| args->type == CMD_ENV_VAR)
			{
				len = ft_strlen(args->token);
				args->token = ft_expand(args->token, len);
			}
			if (token->type == CMD_EXPORT)
				printf("proba export");
			args = args->next;
		}
		token = token->next;
	}
}
