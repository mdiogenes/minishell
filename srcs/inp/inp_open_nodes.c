/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_open_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:28:29 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/23 11:46:49 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_open_pipe(t_ms *mini)
{
	ft_safe_free_char(&mini->stored);
	mini->stored = ft_strdup(mini->line);
	ft_clear_nodes(&mini->first_token, &mini->last_token);
	ft_safe_free_char(&mini->line);
	mini->process = 1;
	mini->line = readline("\e[32mms-42_pipe>\e[0m ");
	if (!mini->line)
	{
		ft_error_comands(ERR_PIPE, MSG_SYNTAX, MSG_ERR_EOF, ft_process_branch);
		return (ERROR);
	}
	mini->line = ft_strjoin_clean_char(&mini->stored, &mini->line, ' ', 0);
	mini->process = 0;
	return (ft_load_input(mini));
}

static inline int	ft_open_quotes(t_ms *mini)
{
	ft_safe_free_char(&mini->stored);
	mini->stored = ft_strjoin(mini->line, "\n");
	ft_clear_nodes(&mini->first_token, &mini->last_token);
	ft_safe_free_char(&mini->line);
	mini->process = 1;
	write(STDIN_FILENO, "\e[32mms-42_quote>\e[0m ", 22);
	mini->line = get_next_line(STDIN_FILENO);
	if (!mini->line)
	{
		ft_error_comands(ERR_GEN, MSG_SYNTAX, MSG_ERR_EOF, ft_process_branch);
		return (ERROR);
	}
	mini->line = ft_strjoin_clean(&mini->stored, &mini->line, 0);
	mini->process = 0;
	return (ft_load_input(mini));
}

static inline int	ft_syntax_redir(t_ms *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->first_token;
	prev = NULL;
	while (token)
	{
		if ((token->meta == MTA_REDIR)
			&& (prev == NULL || (prev->meta >= MTA_REDIR_FILE
					&& prev->meta <= MTA_REDIR && token->meta == prev->meta)))
			return (ft_syntax_error(mini, token->token[0], 1));
		if (!prev && !token->next && token->meta == MTA_REDIR_FILE)
			return (ft_syntax_error(mini, '\n', 1));
		if (!prev && !token->next && token->meta == MTA_OPERATOR)
			return (ft_syntax_error(mini, token->token[0], 2));
		prev = token;
		token = token->next;
	}
	return (SUCCESS);
}

static inline int	ft_check_unclosed(t_ms *mini)
{
	int		count;

	count = ft_count_char(mini->last_token->token, '"');
	if (count % 2 != 0 && mini->last_token->type == CMD_EXPAND)
		return (CMD_EXPAND);
	count = ft_count_char(mini->last_token->token, '\'');
	if (count % 2 != 0 && mini->last_token->type == CMD_LITERAL)
		return (CMD_LITERAL);
	count = ft_count_brakets(mini);
	if (count < 0)
		return (-1);
	else if (count > 0)
		return (OPR_OPEN_K);
	if (mini->last_token->type == RDR_PIPE)
		return (RDR_PIPE);
	if (mini->last_token->type == OPR_AND || mini->last_token->type == OPR_OR)
		return (OPR_AND);
	return (SUCCESS);
}

int	ft_open_nodes(t_ms *mini)
{
	int		rst;
	int		evl;

	if (ft_syntax_redir(mini) == ERROR)
		return (ERROR);
	rst = ft_check_unclosed(mini);
	if (rst != SUCCESS && mini->status == 2)
		exit (ft_error_comands(ERR_EOF, " -c ", MSG_ERR_EOF, ft_free_exit));
	while (rst != SUCCESS)
	{
		if (rst < SUCCESS)
			return (ft_syntax_error(mini, ')', 1));
		if (rst == CMD_EXPAND || rst == CMD_LITERAL)
			evl = ft_open_quotes(mini);
		else if (rst == RDR_PIPE)
			evl = ft_open_pipe(mini);
		else if (rst == OPR_AND)
			evl = ft_open_logic(mini);
		else if (rst == OPR_OPEN_K)
			evl = ft_open_brakets(mini);
		if (evl == ERROR)
			return (ERROR);
		rst = ft_check_unclosed(mini);
	}
	return (SUCCESS);
}
