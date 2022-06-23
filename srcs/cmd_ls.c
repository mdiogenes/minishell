/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:26:59 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/16 15:38:39 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_dir(char *token)
{
	struct stat	data;
	int			eval;

	eval = stat(token, &data);
	if (eval == 0)
		return (S_ISDIR(data.st_mode));
	else
		return (0);
}

int	ft_to_show(char *file, char *filter)
{
	size_t	wp;
	char	*to_find;
	size_t	wilds;

	if (ft_strchr(filter, '*') == NULL)
		return (ft_strict_cmp(file, filter));
	if (ft_strlen(filter) == 1 && filter[0] == '*')
		return (0);
	wp = ft_strict_lenchar(filter, '*');
	wilds = ft_count_char(filter, '*');
	while (wilds > 0)
	{
		if (wp == 0)
			to_find = ft_strndup(&filter[1], ft_strlenchar(&filter[1], '*'));
		else
			to_find = ft_strndup(filter, ft_strlenchar(filter, '*'));
		if (ft_strnstr(file, to_find, ft_strlen(file)) == NULL)
			return (1);
		wilds--;
	}
	return (0);
}

size_t	ft_ls_print(DIR *dir, t_ms *mini)
{
	struct dirent	*files;
	int				list;
	size_t			rst;

	list = 0;
	errno = 0;
	rst = 0;
	while (1)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (list == 5 && printf("\n"))
			list = 0;
		if (ft_strncmp(files->d_name, ".", 1) != 0)
		{
			rst += printf("%-20s - %d ",
					files->d_name, ft_is_dir(files->d_name));
			list++;
		}
	}
	if (errno != 0)
		return (ft_error_handler(errno, mini));
	return (rst);
}

void	ft_get_flags(t_ms *mini, unsigned char *flg, t_token *prev)
{
	t_token	*arg;

	arg = mini->first_token->args;
	while (arg)
	{
		if (arg->token[0] == '-')
		{
			if (ft_count_char(arg->token, 'a') > 0)
				*flg = *flg | (1 << 2);
			if (ft_count_char(arg->token, 'l') > 0)
				*flg = *flg | 1;
			arg = ft_remove_node(arg, prev, &mini->first_token->args);
			continue ;
		}
		if (ft_count_char(arg->token, '*') > 0)
		{
			if (ft_count_char(arg->token, '*') == ft_strlen(arg->token))
				*flg = *flg | (1 << 4);
			arg = ft_remove_node(arg, prev, &mini->first_token->args);
			continue ;
		}
		prev = arg;
		arg = arg->next;
	}
}

t_token	*ft_get_flt(t_ms *mini)
{
	t_token	*arg;
	int		flg;

	arg = mini->first_token->args;
	if (arg == NULL)
		return (NULL);
	flg = 0;
	while (arg)
	{
		if (ft_is_dir(arg->token) == 1)
			flg++;
		else
		{
			if (ft_count_char(arg->token, '*') == 0 && flg > 0)
				return (arg);
			if (ft_count_char(arg->token, '*') > 0)
				return (arg);
		}
		arg = arg->next;
	}
	return (NULL);
}

char	*ft_get_dir(t_ms *mini, t_token *arg)
{
	t_token	*prev;
	char	*rst;

	if (arg == NULL)
		return (NULL);
	prev = NULL;
	while (arg)
	{
		if (ft_is_dir(arg->token) == 1)
		{
			rst = ft_strdup(arg->token);
			ft_remove_node(arg, prev, &mini->first_token->args);
			return (rst);
		}
		arg = arg->next;
	}
	return (ft_strdup(arg->token));
}

int	ft_ls(t_ms *mini)
{
	t_token			*flt;
	DIR				*dir;
	unsigned char	flg;

	flg = 128;
	ft_get_flags(mini, &flg, NULL);
	flt = ft_get_flt(mini);
	if (mini->first_token->args)
		dir = opendir(mini->first_token->args->token);
	else
		dir = opendir(mini->path);
	if (!dir)
	{
		ft_process_branch(mini);
		return (ft_error_handler(errno, mini));
	}
	if (ft_ls_print(dir, mini) != 0)
		printf("\n");
	ft_process_branch(mini);
	closedir(dir);
	mini->exitstatus = 0;
	return (SUCCESS);
}
