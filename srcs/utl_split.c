/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:46:15 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/10 12:46:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_split_word(char **rst, char *str, char *charset, int *it_y_i)
{
	int	x;

	x = 0;
	while (str[it_y_i[1]] && ft_is_charset(str[it_y_i[1]], charset) == 0)
	{
		rst[it_y_i[0]][x] = str[it_y_i[1]];
		x++;
		it_y_i[1]++;
	}
}

static int	ft_word_size(char *str, char *charset, int p)
{
	int	i;

	i = 0;
	while (ft_is_charset(str[p + i], charset) == 0)
		i++;
	return (i);
}

static void	ft_sizes(char *str, char *charset, int *sizes)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_is_charset(str[i], charset) == 1)
			count++;
		i++;
	}
	sizes[0] = i;
	sizes[1] = i - count;
}

char	**ft_split_charset(char *str, char *charset)
{
	int		sz_srw[3];
	char	**rst;
	int		it_y_i[2];

	ft_sizes(str, charset, &sz_srw[0]);
	rst = (char **)malloc(sizeof(char *) * sz_srw[1] + 1);
	if (rst == NULL)
		return (NULL);
	it_y_i[0] = 0;
	it_y_i[1] = 0;
	while (it_y_i[1] < sz_srw[0])
	{
		while (ft_is_charset(str[it_y_i[1]], charset) == 1)
			it_y_i[1]++;
		sz_srw[2] = ft_word_size(str, charset, it_y_i[1]);
		rst[it_y_i[0]] = (char *)malloc(sizeof(char) * sz_srw[2]);
		if (rst[it_y_i[0]] == NULL)
			return (NULL);
		ft_split_word(&rst[0], &str[0], &charset[0], &it_y_i[0]);
		it_y_i[0]++;
	}
	rst[it_y_i[0]] = 0;
	return (rst);
}
