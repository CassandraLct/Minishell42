/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2023/02/01 15:10:52 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 5 fonctions
//recupere les paths possible
//static char	**recup_path(t_min *mini)
char	**recup_path(t_min *mini)
{
	char	**all_path;
	char	*b_path;

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
//static char	**init_cmd(char **cmd, char **pathcmd)
char	**init_cmd(char **cmd, char **pathcmd)
{
	char	*tmp;

	pathcmd = ft_cpytab(cmd);
	tmp = ft_strjoin("/", pathcmd[0]);
	free(pathcmd[0]);
	pathcmd[0] = ft_strdup(tmp);
	free(tmp);
	return (pathcmd);
}

//execute la cmd donner
void	ft_execve(t_min *mini, char **all_path, char **pathcmd, char **cmd)
{
	char	*gd_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (all_path[i])
	{
		gd_path = ft_strjoin(all_path[i], pathcmd[0]);
		if (access(gd_path, R_OK) == 0)
		{
//			free(gd_path);
//			dprintf(2, "before execve, gd_path =[%s] / ", gd_path);
//			dprintf(2, "pathcmd[0]=[%s] / ", pathcmd[0]);
//			dprintf(2, "pathcmd[1]=[%s]\n", pathcmd[1]);
//			dprintf(2, "pathcmd[2]=[%s]\n", pathcmd[2]);
//			dprintf(2, "after printing arg for execve\n");
			if (execve(gd_path, pathcmd, mini->c_env) == -1)
			{
				perror("Execve : ");
				exit(EXIT_FAILURE);
			}
//			dprintf(2, "after execve\n");
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if (j == i)
		aff_errcmd(cmd);
}

//test chaque path puis execute la cmd si existante
void	ft_exec(t_min *mini, char **all_path, char **pathcmd, char **cmd)
{
	if (verif_cmd(all_path, pathcmd, cmd) != 0 || cmd[0][0] == '\0')
	{
//		printf("ici1\n");
		dprintf(2, "wrong command\n");
		free_tab(all_path);
		free_tab(pathcmd);
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
			ft_execve(mini, all_path, pathcmd, cmd);
		else
			waitpid(mini->pid, &mini->ret_err, 0);
		free_tab(all_path);
		free_tab(pathcmd);
	}
}

//a gerer avec un fork pour empecher de sortir de minishell
void	ft_set_pathexec(t_min *mini, char **cmd)
{
	char	**all_path;
	char	**pathcmd;

//	dprintf(2, "cmd[0]=[%s]\n", cmd[0]);
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
	ft_exec(mini, all_path, pathcmd, cmd);
}
