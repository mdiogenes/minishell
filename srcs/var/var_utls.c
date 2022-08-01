/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:22:58 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/15 01:23:05 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_valid_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '_'))
		return (IS_TRUE);
	return (IS_FALSE);
}

int	ft_check_var_name(char *name)
{
	char	c;

	if (!name || ft_strlen_max(name, 1) == 0)
		return (IS_FALSE);
	c = name[0];
	if ((c == '_' || c == '$' || ft_isalpha(c) == IS_TRUE)
		&& (ft_check_by_fnc(name, ft_valid_char) == IS_TRUE))
		return (IS_TRUE);
	return (IS_FALSE);
}
