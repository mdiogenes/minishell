/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 23:23:45 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/10 10:58:14 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_ms *mini)
{
	if (mini->line)
		free (mini->line);
	if (mini->path)
		free (mini->path);
	if (mini->prompt)
		free (mini->prompt);
	if (mini->first_token)
		ft_clear_nodes(mini);
}

void	ft_get_path_prompt(t_ms *mini)
{
	char	pwd[PATH_MAX];
	char	*tmp;

	if (mini->path)
		free (mini->path);
	mini->path = ft_strdup(getcwd(pwd, PATH_MAX));
	if (mini->prompt)
		free (mini->prompt);
	tmp = ft_strjoin("\e[33m[42-ms ", ft_strrchr(getcwd(pwd, PATH_MAX), '/'));
	mini->prompt = ft_strjoin(tmp, "]\e[0m ");
	free (tmp);
}



int	ft_init_minishell(t_ms *mini, char **envp)
{
	int	i;

	i = 0;
//copia variables entorno envp a la estructura dupenvp
	if (!envp || !envp[0])
		return(0);
	while (envp[i])
		i ++;
	mini->dupenvp= malloc(sizeof(char * )*i);
	i = 0;
	while (envp[i])
	{
		mini->dupenvp[i] = ft_strdup(envp[i]);
		i ++;
	}
//liberamos al final del programa 
	mini->status = 1;
	mini->first_token = NULL;
	mini->line = NULL;
	mini->path = NULL;
	mini->prompt = NULL;
	ft_get_path_prompt(mini);
	return (1);
}
