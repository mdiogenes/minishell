/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:54:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/29 10:59:24 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_clear_spaces(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static inline char	*ft_strdup_input(char *src, size_t len, t_ms *mini)
{
	char	*dst;

	dst = (char *)ft_calloc(sizeof(char), (len + 1));
	if (dst == NULL)
		ft_error_free(errno, mini);
	dst[len] = '\0';
	while (len--)
		dst[len] = src[len];
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

int	ft_load_input(t_ms *mini)
{
	size_t		i;
	size_t		len;

	i = -1;
	mini->line = ft_strtrim_clean(mini->line, " \n\t");
	while (mini->line[++i])
	{
		while (ft_clear_spaces(mini->line[i]))
			i++;
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
		if (mini->line[i] == '=' && mini->line[i - 1])
			ft_export_fix(&mini->line[i - 1], &len, &i);
		ft_inp_append(&mini->first_token, ft_inp_new(
				ft_strdup_input(&mini->line[i], len, mini), mini));
		i = i + len - 1;
	}
	return (SUCCESS);
}
