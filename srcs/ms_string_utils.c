/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:27:39 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 09:16:45 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_reserved(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '=');
}

int	ft_is_buildin(char c)
{
	return (c == '>');
}

char	**join_str(char **dst, char **str, int in, int fin)
{
	if (!*dst)
		*dst = ft_substr(*str, in, fin);
	else
		*dst = ft_strjoin(*dst, ft_substr(*str, in, fin));
	return (dst);
}
