/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/20 11:18:44 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_var(char **dst, int i, int j, char **str)
{
	char	*var;
	char	*proba;
	int		len;

	//ULL no se si inicialitzar aixi
	var = NULL;
	//var = malloc(sizeof(char));
	//dst ho hauriem de inicialitzar dalguna manera??
	
	if ( !*dst)
		*dst = ft_substr(*str, j, i -j);
	else
		*dst = ft_strjoin(*dst, ft_substr(*str, j, i - j));
	i ++;
	j = i;
	while ((*str)[i] != ' ' && i < (int)ft_strlen(*str) && (*str)[i] != '$')
	i++;
	//hauria de fer malloc de la variable VAr?
	proba = ft_substr(*str, j, i -j);
	len = ft_strlen(getenv((const char *)proba));
	var = malloc(sizeof(char)*len + 1);
	var = getenv((const char *)proba);
	free (proba);
	if (var)
		*dst = ft_strjoin(*dst, var);
	else
		*dst = ft_strjoin(*dst, "\0");
//no ESTIC ALLIBERANT VAR!!!!!!!!! OJOOOOOOOO
	//if (var)
	//	free (var);
	return (i);
}

char	*ft_expand(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	//ULLL no se si inicicallitar aixi
	//dst = malloc(sizeof(char));
	dst = NULL;
	while (str[i])
	{	
		if (str[i] == '$')
		{	
			i = ft_change_var(&dst, i, j, &str);
			j = i;
		}
		if ((str[i] != '$') || !str[i + 1]
			|| ((str[i] == '$' && ((str[i + 1] == ' ') || str[i + 1] == '?'))))
		{
			i ++;
			while (str[i + 1] == '$')
				i ++;
			if (str[i] == '$' && (str[i + 1] == ' '))
				i ++;
			if ((str[i] == '$') && (str[i + 1] == '?'))
			{
				i ++;
				if ( !dst)
					dst = ft_substr(str, j, i -j -1);
				else
					dst = ft_strjoin(dst, ft_substr(str, j, i - j - 1));
				j = i + 1;
				dst = ft_strjoin(dst, "lastpipe");
			}
		}
	}
	if (i > j)
	{
		if ( !dst)
			dst = ft_substr(str, j, i -j);
		else
		dst = ft_strjoin(dst, ft_substr(str, j, i - j));
	}
	if (str)
		free(str);
	return (dst);
}
//$$ tampoc surt igual que el bash nos en borrem un dels 2
//$$? fem igual que $$

void	ft_get_expand(t_ms	*mini)
{
	t_token	*token;
	t_token *args;

	token = mini->first_token;
	args = mini->first_token->args;
	while (token)
	{
		while (args)
		{	
			if (args->type == CMD_EXPAND || args->type == NO_TYPE)
			{	
				args->token = ft_expand(args->token);
			}
			args = args->next;
		}
		token = token->next;
	}	
}
