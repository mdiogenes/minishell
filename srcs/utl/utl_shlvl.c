/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:32:19 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/07 01:32:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_shlvl_rst(char *value)
{
	int	level;

	level = 0;
	if (ft_send_to_atoi(value) == 1)
	{
		level = ft_atoi(value);
		if (level > 999)
			level = ft_shlvl_err();
		if (level < 0)
			level = -1;
	}
	else
		level = 0;
	return (level);
}

void	ft_shlvl_check(t_ms *mini)
{
	t_token	*shlvl;
	char	*val;

	shlvl = ft_find_envar_export("SHLVL", mini);
	val = NULL;
	if (shlvl == NULL)
		ft_export_var("SHLVL", "1", 0, mini);
	else
	{
		if (shlvl->args)
		{
			val = ft_itoa(ft_shlvl_rst(shlvl->args->token) + 1);
			ft_export_var("SHLVL", val, 0, mini);
		}
		else
			ft_export_var("SHLVL", "1", 0, mini);
	}
	ft_safe_free_char(&val);
}
