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
	if (mini->line)
		free (mini->line);
	while (1)
	{
		mini->line = readline("\e[32mms-42_pipe>\e[0m ");
		if (!mini->line)
			return (ft_error_comands(ERR_PIPE, MSG_SYNTAX, MSG_ERR_EOF, mini));
		if (ft_strlen(mini->line) > 0)
			return (ft_load_input(mini));
	}
}

static inline int	ft_open_quotes(t_ms *mini, t_token *token,
			t_token *prev, char quote)
{
	char	*rst;

	rst = ft_strjoin(token->token, "\n");
	while (1)
	{
		if (mini->line)
			free (mini->line);
		write(STDIN_FILENO, "\e[32mms-42_quote>\e[0m ", 22);
		mini->line = get_next_line(STDIN_FILENO);
		if (!mini->line)
			return (ft_error_comands(ERR_GEN, MSG_SYNTAX, MSG_ERR_EOF, mini));
		if (ft_count_char(mini->line, quote) > 0)
		{
			mini->line = ft_strnjoin_clean(rst, mini->line,
					ft_strlen(rst), ft_strlen(mini->line));
			prev->next = NULL;
			ft_delete_node(token);
			return (ft_load_input(mini));
		}
		rst = ft_strjoin_clean(rst, mini->line, 1);
	}
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
		prev = token;
		token = token->next;
	}
	return (SUCCESS);
}

static inline int	ft_check_unclosed(t_token **node, t_token **last)
{
	t_token	*token;
	t_token	*prev;
	int		count;

	token = *node;
	prev = *last;
	while (token && token->next != NULL)
	{
		prev = token;
		token = token->next;
	}
	*node = token;
	*last = prev;
	count = ft_count_char(token->token, '"');
	if (count % 2 != 0)
		return (CMD_EXPAND);
	count = ft_count_char(token->token, '\'');
	if (count % 2 != 0)
		return (CMD_LITERAL);
	if (token->type == RDR_PIPE && token->next == NULL)
		return (RDR_PIPE);
	return (SUCCESS);
}

int	ft_open_nodes(t_ms *mini)
{
	t_token	*token;
	t_token	*prev;
	int		rst;

	if (ft_syntax_redir(mini) == ERROR)
		return (ERROR);
	token = mini->first_token;
	prev = NULL;
	rst = ft_check_unclosed(&token, &prev);
	while (rst != SUCCESS)
	{
		if (rst == CMD_EXPAND)
			ft_open_quotes(mini, token, prev, '"');
		else if (rst == CMD_LITERAL)
			ft_open_quotes(mini, token, prev, '\'');
		else if (rst == RDR_PIPE)
			ft_open_pipe(mini);
		prev = NULL;
		token = mini->first_token;
		rst = ft_check_unclosed(&token, &prev);
	}
	return (SUCCESS);
}
