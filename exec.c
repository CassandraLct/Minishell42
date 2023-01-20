/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2023/01/20 18:44:35 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 5 fonctions
//recupere les paths possible
static char	**recup_path(t_min *mini)
{
	char	**all_path;
	char	*b_path;
	int		i;

	i = 0;
	b_path = NULL;
	b_path = recup_pathexec(mini);
	if (b_path == NULL)
	{
		all_path = NULL;
		g_mini.ret_err = 127;
	}
	else
	{
		all_path = ft_split(b_path, ':');
		free(b_path);
	}
	return (all_path);
}

//initialise le tableau
static char	**init_cmd(char **tab, char **cmd)
{
	char	*tmp;

	cmd = ft_cpytab(tab);
	tmp = ft_strjoin("/", cmd[0]);
	free(cmd[0]);
	cmd[0] = ft_strdup(tmp);
	free(tmp);
	return (cmd);
}

//execute la cmd donner
void	ft_execve(t_min *mini, char **all_path, char **cmd)
{
	char	*gd_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (all_path[i])
	{
		gd_path = ft_strjoin(all_path[i], cmd[0]);
		if (access(gd_path, R_OK) == 0)
		{
			free(gd_path);
			if (execve(gd_path, cmd, mini->c_env) == -1)
			{
				perror("Execve : ");
				exit(EXIT_FAILURE);
			}
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if (j == i)
		aff_errcmd();
}

//test chaque path puis execute la cmd si existante
void	ft_exec(t_min *mini, char **all_path, char **cmd)
{
	if (verif_cmd(all_path, cmd) != 0)
	{
		free_tab(all_path);
		free_tab(cmd);
		return ;
	}
	else
	{
		mini->pid = fork();
		if (mini->pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (mini->pid == 0)
			ft_execve(mini, all_path, cmd);
		else
			waitpid(mini->pid, &mini->ret_err, 0);
		free_tab(all_path);
		free_tab(cmd);
	}
}

//a gerer avec un fork pour empecher de sortir de minishell
void	ft_set_pathexec(t_min *mini, char **cmd)
{
	char	**all_path;
	char	**pathcmd;

	pathcmd = NULL;
	pathcmd = init_cmd(cmd, pathcmd);
	all_path = recup_path(mini);
	if (all_path == NULL)
	{
		mini->ret_err = 127;
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		free_tab(pathcmd);
		return ;
	}
	ft_exec(mini, all_path, pathcmd);
}
