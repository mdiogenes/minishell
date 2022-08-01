/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/07/08 12:26:26 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_caseinterr_digit(char *str,
		char **dst, int *i_j, t_ms *mini)
{
	char	*tmp;

	ft_safe_free_char(&mini->stored);
	mini->stored = ft_itoa(mini->exitstatus);
	if ((str[i_j[0]] == '$') && (str[i_j[0] + 1] == '?'))
	{
		tmp = ft_substr(str, i_j[1], i_j[0] - i_j[1]);
		if (!*dst)
			*dst = ft_strjoin_clean(&tmp, &mini->stored, 0);
		else
		{
			tmp = ft_strjoin_clean(dst, &tmp, 0);
			*dst = ft_strjoin_clean(&tmp, &mini->stored, 0);
		}
		i_j[0] = i_j[0] + 1;
		i_j[1] = i_j[0] + 1;
	}
	if ((str[i_j[0]] == '$') && (ft_isdigit(str[i_j[0] + 1])))
	{
		ft_join_str(dst, &str, i_j[1], i_j[0] - i_j[1]);
		i_j[0] = i_j[0] + 2;
		i_j[1] = i_j[0];
	}
}

static inline void	ft_rarecase(char *str, char **dst, int *i_j, t_ms *mini)
{
	int		len;
	int		sp;

	len = ft_strlen(str);
	sp = 1;
	if (i_j[0] + 1 < len)
	{
		if ((str[i_j[0]] == '$') && (str[i_j[0] + 1] && str[i_j[0] + 1] == '$'))
		{
			join_dst_pid(str, dst, &i_j[0], mini);
			i_j[0] = i_j[0] + 1;
			i_j[1] = i_j[0] + 1;
			i_j[0] = i_j[0] + 1;
		}
		if (str[i_j[0]] == '$' && (!str[i_j[0] + 1]
				|| ((str[i_j[0] + 1] && ft_is_space(str[i_j[0] + 1])))))
		{
			while (str[i_j[0] + sp] && str[i_j[0] + sp] != '$')
				sp++;
			ft_join_str(dst, &str, i_j[1], i_j[0] - i_j[1] + sp);
			i_j[0] = i_j[0] + sp;
			i_j[1] = i_j[0];
		}
		ft_caseinterr_digit(str, dst, &i_j[0], mini);
	}
}

void	ft_jump_str(char *token, int *i_j)
{
	if (token[i_j[0]] == '\\'
		&& (token[i_j[0] + 1]
			&& token[i_j[0] + 1] == '$'))
		i_j[0] += 2;
	if (token[i_j[0]] != '$' || !token[i_j[0] + 1])
			i_j[0]++;
}

int	ft_do_expand(t_ms *mini, t_token *node)
{
	char		*dst;
	int			i_j[2];

	dst = NULL;
	if (node->type == CMD_LITERAL || node->meta == MTA_NULL_TOKEN
		|| ft_strlen_max(node->token, 1) == 0
		|| ft_count_char(node->token, '$') == 0)
		return (ERROR);
	ft_init_vector(&i_j[0], 0, 2);
	while (i_j[0] < (int)ft_strlen(node->token))
	{
		ft_jump_str(node->token, &i_j[0]);
		if ((node->token[i_j[0]] == '$') && (node->token[i_j[0] + 1] != '?')
			&& (i_j[0] + 1 < (int)ft_strlen(node->token))
			&& (node->token[i_j[0] + 1] != '$')
			&& (node->token[i_j[0] + 1] != ' ')
			&& (!ft_isdigit(node->token[i_j[0] + 1])))
			ft_change_var(&dst, &i_j[0], &node->token, node);
		ft_rarecase(node->token, &dst, &i_j[0], mini);
	}
	if (i_j[0] > i_j[1])
		ft_join_str(&dst, &node->token, i_j[1], i_j[0] - i_j[1]);
	ft_safe_free_char(&node->token);
	node->token = dst;
	return (SUCCESS);
}

int	ft_get_expand(t_ms *mini, t_token *node, int (*ft_exp)(t_ms *, t_token *))
{
	if (!node)
		return (SUCCESS);
	if (node->meta >= MTA_NEXT)
		return (SUCCESS);
	if (!node->args && !node->next)
		return (ft_exp(mini, node));
	if (node->args && node->next)
		return (ft_get_expand(mini, node->args, ft_exp)
			+ ft_get_expand(mini, node->next, ft_exp)
			+ ft_exp(mini, node));
	if (!node->args && node->next)
		return (ft_get_expand(mini, node->next, ft_exp)
			+ ft_exp(mini, node));
	return (ft_get_expand(mini, node->args, ft_exp)
		+ ft_exp(mini, node));
}
