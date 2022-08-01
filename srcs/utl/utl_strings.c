/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:27:39 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:34:12 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_is_reserved(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '\"'
		|| c == ';' || c == '(' || c == ')' || c == '\'');
}

void	ft_join_str(char **dst, char **str, int in, int fin)
{
	char	*tmp;
	char	*sub_str;

	sub_str = ft_substr(*str, in, fin);
	if (!*dst)
		*dst = sub_str;
	else
	{
		tmp = ft_strjoin_clean(dst, &sub_str, 0);
		*dst = tmp;
	}
}

void	join_dst_pid(char *str, char **dst, int *i_j, t_ms *mini)
{
	char	*tmp;
	char	*pid;

	pid = ft_itoa(mini->pid);
	tmp = ft_substr(str, i_j[1], i_j[0] - i_j[1]);
	if (!*dst)
		*dst = ft_strjoin_clean(&tmp, &pid, 0);
	else
	{
		tmp = ft_strjoin_clean(dst, &tmp, 0);
		*dst = ft_strjoin_clean(&tmp, &pid, 0);
	}
}
