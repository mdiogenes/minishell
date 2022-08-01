/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:54:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 11:10:11 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_clear_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		i++;
	return (i);
}

static inline char	*ft_strdup_input(char *src, size_t len,
	size_t i, t_ms *mini)
{
	char	*dst;

	if (i > 0 && ft_is_space(src[i - 1]) == IS_TRUE)
		mini->sp_tkn = 1;
	mini->sp_tkn = mini->sp_tkn << 2;
	if (src[i + len] && ft_is_space(src[i + len]) == IS_TRUE)
		mini->sp_tkn |= 1;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		ft_error_free(errno, mini);
	dst[len] = 0;
	while (len--)
		dst[len] = src[i + len];
	return (dst);
}

static inline size_t	ft_strlen_chars(const char *s, char c)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = -1;
	while (s[i] && flag < 1)
	{
		if (flag == 1)
			break ;
		if (s[i] == c)
			flag++;
		if (flag < 1 && !s[i + 1])
		{
			return (i + 1);
			break ;
		}
		i++;
	}
	return (i);
}

int	ft_final_load(t_ms *mini)
{
	if (ft_workflow_check(mini) != SUCCESS)
		return (ERROR);
	if (ft_open_nodes(mini) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	ft_load_input(t_ms *mini)
{
	size_t		i;
	size_t		len;

	i = 0;
	mini->line = ft_strtrim_clean(mini->line, " \n\t");
	if (ft_strlen_max(mini->line, 1) == 0)
		return (ERROR);
	while (mini->line[i])
	{
		i = ft_clear_spaces(mini->line, i);
		if (mini->line[i] == '\'' || mini->line[i] == '\"')
			len = ft_strlen_chars(&mini->line[i], mini->line[i]);
		else
		{
			if (ft_load_strlen(mini, &mini->line[i],
					ft_is_reserved(mini->line[i]), &len) == ERROR)
				return (ERROR);
		}
		if (mini->line[i] == '(' || mini->line[i] == ')')
			len = 1;
		ft_new_token(mini, ft_inp_new(
				ft_strdup_input(mini->line, len, i, mini), mini));
		i = i + len;
	}
	return (ft_final_load(mini));
}
