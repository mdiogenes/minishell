/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:54:43 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 13:50:21 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static inline size_t	ft_strlen_to(const char *s, int scn)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != ' ' && ft_is_reserved(s[i]) == (1 * scn))
		i++;
	return (i);
}

static inline size_t	ft_strlen_chars(const char *s, char c)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = -1;
	while (s[i] && ((s[i] == c && flag < 1) || s[i] != c))
	{
		if (flag == 1)
			break ;
		if (s[i] == c)
			flag++;
		i++;
	}
	return (i);
}

void	ft_export_fix(const char *s, size_t *len, size_t *i)
{
	size_t	k;

	k = 0;
	if (s[k] != ' ' && (s[k + 2] && s[k + 2] != ' '))
		return ;
	if (s[k] == ' ')
	{
		*(len) = *(len) + 1;
		*(i) = *(i) - 1;
	}
	if (s[k + 2] && s[k + 2] == ' ')
		*(len) = *(len) + 1;
}

int	ft_load_input(t_ms *mini)
{
	size_t		i;
	size_t		len;
	char		*tmp;

	i = 0;
	while (mini->line[i])
	{
		if (mini->line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (mini->line[i] == 34 || mini->line[i] == 39)
			len = ft_strlen_chars(&mini->line[i], mini->line[i]);
		else
			len = ft_strlen_to(&mini->line[i],
					ft_is_reserved(mini->line[i]));
		if (mini->line[i] == '=' && mini->line[i - 1])
			ft_export_fix(&mini->line[i - 1], &len, &i);
		tmp = ft_strdup_input(&mini->line[i], len, mini);
		ft_inp_append(&mini->first_token, ft_inp_new(tmp, mini));
		i = i + len;
	}
	return (SUCCESS);
}
