/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 16:49:24 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 3 fonctions
//recupere les paths possible
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

//initialise le tableau de cmd
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
			if (execve(gd_path, pathcmd, mini->c_env) == -1)
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
		aff_errcmd(cmd);
}
