/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:54:13 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/27 12:54:37 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_get_split(char ***tab, t_token *token)
{
	*tab = ft_split(token->token, ' ');
	if (*tab[0] == NULL)
	{
		ft_clear_tabs(*tab);
		return (ERROR);
	}
	return (SUCCESS);
}

static inline char	*ft_build_var(char **tab)
{
	char	*rst;
	int		i;

	i = 0;
	rst = NULL;
	while (tab[i])
	{
		if (rst == NULL)
			rst = ft_strdup(tab[i]);
		else
			rst = ft_strjoin_clean_char(&rst, &tab[i], ' ', 1);
		i++;
	}
	return (rst);
}

static inline char	*ft_get_var(t_token *var, t_token *node)
{
	char	*rst;
	char	**tab;

	if (!var || !var->args || !var->args->token)
		return (NULL);
	else
	{
		if (node->type == CMD_ENV_VAR)
		{
			if (ft_get_split(&tab, var->args) == ERROR)
			{
				rst = ft_strdup(var->args->token);
				return (rst);
			}
			rst = ft_build_var(tab);
			ft_clear_tabs(tab);
			return (rst);
		}
		rst = ft_strdup(var->args->token);
		return (rst);
	}
}

void	ft_change_var(char **dst, int *i_j, char **str, t_token *node)
{
	t_token	*envar;
	char	*var;
	char	*sub_str;

	var = NULL;
	i_j[0] = i_j[0];
	i_j[1] = i_j[1];
	ft_join_str(dst, str, i_j[1], i_j[0] - i_j[1]);
	i_j[0] = i_j[0] + 1;
	i_j[1] = i_j[0];
	while ((*str)[i_j[0]] != ' ' && (i_j[0] < (int)ft_strlen(*str))
		&& (*str)[i_j[0]] != '$' && (*str)[i_j[0]] != '\''
		&& (*str)[i_j[0]] != '/' && (*str)[i_j[0]] != '='
		&& (*str)[i_j[0]] != '\\')
		i_j[0] = i_j[0] + 1;
	sub_str = ft_substr((*str), i_j[1], i_j[0] - i_j[1]);
	envar = ft_find_envar_export(sub_str, g_mini);
	free (sub_str);
	var = ft_get_var(envar, node);
	if (var)
		*dst = ft_strjoin_clean(dst, &var, 0);
	else
		*dst = ft_strjoin_clean_one(dst, "\0");
	i_j[1] = i_j[0];
}
