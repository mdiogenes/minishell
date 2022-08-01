/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:02:20 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/08 12:54:03 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_dup_pipes(t_ms *mini, int n)
{
	if (mini->first_token->out == TKN_STDOUT
		&& mini->first_token->in == TKN_STDIN)
		return ;
	if (mini->first_token->out == TKN_PIPEOUT)
	{
		close(mini->pipes[n][PIPE_READ]);
		if (mini->first_token->to_out == 2)
			dup2(mini->pipes[n][PIPE_WRITE], STDERR_FILENO);
		else
			dup2(mini->pipes[n][PIPE_WRITE], STDOUT_FILENO);
		close(mini->pipes[n][PIPE_WRITE]);
	}
	if (mini->first_token->in == TKN_PIPEIN)
	{
		close(mini->pipes[n - 1][PIPE_WRITE]);
		dup2(mini->pipes[n - 1][PIPE_READ], STDIN_FILENO);
		close(mini->pipes[n - 1][PIPE_READ]);
	}
}

static inline void	ft_child_sandbox(t_ms *mini, int n, int (f)(t_ms *))
{
	unsigned char	fd_to;

	fd_to = mini->first_token->to_out;
	if (f)
		f(mini);
	(void)n;
	if (fd_to == 2)
		close (STDERR_FILENO);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	exit(mini->exitstatus);
}

static inline void	ft_child_exec(t_ms *mini, char *argv[], char **envp, int n)
{
	ft_dup_pipes(mini, n);
	mini->pid_child = 1;
	if (mini->first_token->meta == MTA_BUILDIN)
		ft_child_sandbox(mini, n, ft_build_in);
	if (mini->first_token->meta == MTA_KEYS)
		ft_sub_mini(mini);
	if (mini->first_token->type == RDR_TO_FILE
		|| mini->first_token->type == RDR_APP_FILE)
		ft_child_sandbox(mini, n, ft_dup_file);
	else if (mini->first_token->type == IMP_FROM_FILE)
		ft_child_sandbox(mini, n, ft_inp_from_file);
	else if (mini->first_token->type == IMP_HEREDOC)
		ft_child_sandbox(mini, n, ft_heredoc);
	execve(argv[0], argv, envp);
	ft_error_comands(ERR_CMD, argv[0], MSG_ERR_CMD, ft_process_branch);
	exit (mini->exitstatus);
}

int	ft_child_monitor(t_ms *mini, int total, pid_t lastpid)
{
	int		status;
	int		sig;
	pid_t	child;

	while (--total >= 0)
	{
		child = waitpid(-1, &status, 0);
		if (child == lastpid)
		{
			mini->exitstatus = WEXITSTATUS(status);
			if (WIFSIGNALED(status) != 0)
			{
				sig = WTERMSIG(status);
				if (sig != 13)
					ft_child_signals_msg(sig);
				else
					mini->exitstatus = 127;
			}
		}
	}
	mini->process = 0;
	return (SUCCESS);
}

pid_t	ft_fork_and_run(t_ms *mini, int n, int (*process)(t_ms *),
		int (*wait_exit)(t_ms *, int, pid_t))
{
	char	**argv;
	char	**argenv;

	argv = ft_build_argv(mini, mini->first_token);
	argenv = ft_build_arenv(mini);
	mini->pid_child = fork();
	if (mini->pid_child == -1)
		return (ft_fork_err(mini));
	if (mini->pid_child > 0)
	{
		ft_clear_tabs(argv);
		ft_clear_tabs(argenv);
	}
	if (mini->pid_child == 0)
		ft_child_exec(mini, argv, argenv, n);
	if (wait_exit)
		wait_exit(mini, n, mini->pid_child);
	if (process)
		process(mini);
	return (mini->pid_child);
}
