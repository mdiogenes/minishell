/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:02:20 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/20 16:44:24 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_child_monitor(t_ms *mini, int n, pid_t child)
{
	int	status;
	int	sig;

	if (n > -1 && mini->first_token->in == TKN_PIPEIN)
	{
		close(mini->pipes[n - 1][PIPE_READ]);
		close(mini->pipes[n - 1][PIPE_WRITE]);
	}
	waitpid(child, &status, 0);
	mini->exitstatus = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
	{
		sig = WTERMSIG(status);
		mini->exitstatus = sig | 128;
		ft_child_signals_msg(sig);
	}
	return (SUCCESS);
}

static inline void	ft_dup_pipes(t_ms *mini, int *n)
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

void	ft_child_exec(t_ms *mini, char **argv, char **envp, int n)
{
	mini_getpid(mini);
	ft_dup_pipes(mini, &n);
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
	ft_close_pipes(mini, n);
	ft_error_comands(ERR_CMD, argv[0], MSG_ERR_CMD, mini);
	if (errno == ENOENT)
		exit (127);
	else
		exit (126);
}

int	ft_fork_and_run(t_ms *mini, int n, int (*process)(t_ms *))
{
	pid_t	fork_pid;
	char	**argv;
	char	**argenv;
	int		rst;

	ft_prepare_node(mini, mini->first_token);
	argv = ft_build_argv(mini, mini->first_token);
	argenv = ft_build_arenv(mini);
	fork_pid = fork();
	if (fork_pid > 0)
	{
		rst = ft_child_monitor(mini, n, fork_pid);
		ft_clear_tabs(argv);
		ft_clear_tabs(argenv);
		if (process)
			process(mini);
		return (rst);
	}
	if (fork_pid == 0)
		ft_child_exec(mini, argv, argv, n);
	return (SUCCESS);
}
