/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:48:21 by msoler-e          #+#    #+#             */
/*   Updated: 2022/06/22 14:18:20 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_ls_print(DIR *dir, t_ms *mini, char *pattern)
{
	struct dirent	*files;
	int				rst;
	int				flt;

	rst = 0;
	while (1)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (pattern == NULL)
			flt = ft_strncmp(files->d_name, ".", 1);
		else
			flt = ft_regex(files->d_name, pattern);
		if (flt != IS_FALSE)
		{
			if (rst != 0)
				printf(" ");
			rst += printf("%s", files->d_name);
		}
	}
	if (errno != 0)
		return (ft_error_handler(errno, mini));
	return (SUCCESS);
}

int	ft_echo_ls(t_ms *mini, char *pattern)
{
	DIR	*dir;
	int	rst;

	dir = opendir(mini->path);
	rst = 0;
	if (!dir)
		return (ft_error_handler(errno, mini));
	rst = ft_echo_ls_print(dir, mini, pattern);
	if (rst != 0)
		printf("\n");
	closedir(dir);
	mini->exitstatus = 0;
	return (SUCCESS);
}

void	ft_echo_wild(t_token *token, t_ms *mini)
{
	if (ft_strict_cmp(token->token, "*") == 0)
		ft_echo_ls(mini, NULL);
	else
		ft_echo_ls(mini, token->token);
}

int	ft_echo_args(t_ms *mini, t_token *args, int opcio)
{
	t_token	*token;	
	int		n;

	n = 0;
	token = args;
	while (token)
	{
		if (ft_strict_lenchar(token->token, '*') > -1)
			ft_echo_wild(token, mini);
		else if (token->token != NULL)
		{
			if ((ft_strict_cmp(token->token, "-n") == 0) && n == 0)
				opcio = 1;
			else
			{
				n = 1;
				ft_putstr_fd(token->token, STDOUT_FILENO);
			}
			if (token->next && (opcio == 0 || n == 1))
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		token = token->next;
	}
	return (opcio);
}

int	ft_echo(t_ms *mini)
{
	int		opcio;

	opcio = 0;
	opcio = ft_echo_args(mini, mini->first_token->args, opcio);
	if (opcio == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	ft_process_branch(mini);
	return (SUCCESS);
}
