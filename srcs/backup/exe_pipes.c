/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/17 15:21:33 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(t_ms *mini, int n)
{
	close(mini->pipes[n][PIPE_READ]);
	close(mini->pipes[n][PIPE_WRITE]);
}

static inline int	**ft_build_pipes(int n, t_ms *mini)
{
	int	**rst;

	rst = (int **)malloc(sizeof(int *) * n);
	if (!rst)
		ft_error_free(errno, mini);
	while (n--)
		rst[n] = (int *)malloc(sizeof(int) * 2);
	return (rst);
}

static inline int	ft_count_pipes(t_ms *mini)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		i++;
		token = token->next;
	}
	if (i < 2)
		return (1);
	return (i - 1);
}
//////

int	ft_child_monitor_test(t_ms *mini, int n)
{
	int	status;
	int	sig;

	while (n-- >= 0)
	{
		waitpid(-1, &status, 0);
		//printf ("llego el primero\n");
		mini->exitstatus = WEXITSTATUS(status);
		if (WIFSIGNALED(status) != 0)
		{
			sig = WTERMSIG(status);
			if (sig != 13)
			{
				mini->exitstatus = sig | 128;
				ft_child_signals_msg(sig);
			}
			else
				mini->exitstatus = 0;
		}
	}
	return (SUCCESS);
}

static inline void	ft_dup_pipes_test(t_ms *mini, int *n)
{
	if (*(n) < 0 || (mini->first_token->out == TKN_STDOUT
		&& mini->first_token->in == TKN_STDIN))
	return ;
	if (mini->first_token->out == TKN_PIPEOUT)
		dup2(mini->pipes[*(n)][PIPE_WRITE], STDOUT_FILENO);
	if (mini->first_token->in == TKN_PIPEIN)
	{
		*(n) -= 1;
		dup2(mini->pipes[*(n)][PIPE_READ], STDIN_FILENO);
	}
	ft_close_pipes(mini, *(n));
}

void	ft_child_exec_test(t_ms *mini, char **argv, char **envp, int n)
{
	mini_getpid(mini);
	ft_dup_pipes_test(mini, &n);
	if (mini->first_token->meta == MTA_BUILDIN)
		ft_child_sandbox(mini, ft_build_in, n);
	if (mini->first_token->meta == MTA_KEYS)
		ft_sub_mini(mini);
	if (mini->first_token->type == RDR_TO_FILE
		|| mini->first_token->type == RDR_APP_FILE)
		ft_child_sandbox(mini, ft_dup_file, n);
	else if (mini->first_token->type == IMP_FROM_FILE)
		ft_child_sandbox(mini, ft_inp_from_file, n);
	else if (mini->first_token->type == IMP_HEREDOC)
		ft_child_sandbox(mini, ft_heredoc, n);
	execve(argv[0], argv, envp);
	ft_error_comands(ERR_CMD, argv[0], MSG_ERR_CMD, mini);
	if (errno == ENOENT)
		exit (127);
	else
		exit (126);
}

int	ft_fork_and_run_test(t_ms *mini, int n, int (*process)(t_ms *))
{
	pid_t	fork_pid;
	char	**argv;
	char	**argenv;

	ft_prepare_node(mini, mini->first_token);
	argv = ft_build_argv(mini, mini->first_token);
	argenv = ft_build_arenv(mini);
	fork_pid = fork();
	if (fork_pid > 0)
	{
		ft_clear_tabs(argv);
		ft_clear_tabs(argenv);
		if (process)
			process(mini);
		return (SUCCESS);
	}
	if (fork_pid == 0)
		ft_child_exec(mini, argv, argv, n);
	return (SUCCESS);
}


int	ft_pipes(t_ms *mini)
{
	t_token	*token;
	int		n;
	int total;

	total = ft_count_pipes(mini);
	mini->pipes = ft_build_pipes(ft_count_pipes(mini), mini);
	n = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		ft_fork_and_run_test(mini, n, ft_process_branch);
		if (token->in == TKN_PIPEIN)
			ft_close_pipes(mini, n - 1);
		token = mini->first_token;
		n++;
	}
	ft_child_monitor_test(mini, total);
	return (SUCCESS);
}

/*
int	ft_pipes(t_ms *mini)
{
	t_token	*token;
	int		n;

	mini->pipes = ft_build_pipes(ft_count_pipes(mini), mini);
	n = 0;
	token = mini->first_token;
	while (token && (token->in == TKN_PIPEIN || token->out == TKN_PIPEOUT))
	{
		if (token->out == TKN_PIPEOUT)
			pipe(mini->pipes[n]);
		ft_fork_and_run(mini, n, ft_process_branch);
		token = mini->first_token;
		n++;
	}
	return (SUCCESS);
}
*/