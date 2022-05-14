/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:21:52 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/12 21:21:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pipe_exec(t_ms *mini, char **argv, int n)
{
	if (n % 2)
		dup2(mini->fd[PIPE_WRITE], STDOUT_FILENO);
	else
		dup2(mini->fd[PIPE_READ], STDIN_FILENO);
	close(mini->fd[PIPE_READ]);
	close(mini->fd[PIPE_WRITE]);
	execve(argv[0], argv, NULL);
}

int ft_pipes(t_ms *mini)
{
	pid_t	cpid;
	int		status;
	char	**argv;
	t_token	*node;
	int n;

	n = 1;
	node = mini->first_token;
	pipe(mini->fd);
	while (n <= 2)
	{
		argv = ft_build_argv(mini);
		cpid = fork();
		if (cpid == 0)
			ft_pipe_exec(mini, argv, n);
		ft_clear_tabs(argv);
		n++;
	}
	close(mini->fd[PIPE_READ]);
	close(mini->fd[PIPE_WRITE]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return(SUCCESS);
}

/*
int ft_pipes(t_ms *mini)
{
	pid_t cpid;
	int 	status;
	char **argv;

	ft_process_node(mini);
	pipe(mini->fd);
	argv = ft_build_argv(mini);
	cpid = fork();
	if (cpid == 0)
	{
		dup2(mini->fd[PIPE_WRITE], STDOUT_FILENO);
		close(mini->fd[PIPE_READ]);
		close(mini->fd[PIPE_WRITE]);
		execve(argv[0], argv, NULL);
	}
	ft_process_brach(mini);
	argv = ft_build_argv(mini);
	cpid = fork();
	if (cpid == 0)
	{
		dup2(mini->fd[PIPE_READ], STDIN_FILENO);
		close(mini->fd[PIPE_READ]);
		close(mini->fd[PIPE_WRITE]);
		execve(argv[0], argv, NULL);
	}
	ft_process_brach(mini);
	close(mini->fd[PIPE_READ]);
	close(mini->fd[PIPE_WRITE]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return(SUCCESS);
}
*/