/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2022/12/20 12:39:30 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//recupere les paths possible
static char	**recup_path(t_min mini)
{
	char	**all_path;
	char	*b_path;
	int		i;

	i = 0;
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], "PATH=", 5) == 0)
			b_path = ft_strdup(mini.c_env[i] + 5);
		i++;
	}
	i = 0;
	all_path = ft_split(b_path, ':');
	free(b_path);
	return (all_path);
}

//initialise le tableau
static char	**init_cmd(char **tab, char **cmd)
{
	cmd = NULL;
	cmd = init_cpy(tab, cmd);
	cmd = ft_cpytab(tab);
	cmd[0] = ft_strjoin("/", cmd[0]);
	return (cmd);
}

//test chaque path puis execute la cmd si existante
void	ft_exec(t_min mini, char **all_path, char **cmd)
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
			if (execve(gd_path, cmd, mini.c_env) == -1)
				perror("Execve : ");
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if (j == i)
		printf("minishell: %s: command not found\n", mini.tab[0]);
}

//a gerer avec un fork pour empecher de sortir de minishell
void	ft_set_pathexec(t_min mini)
{
	char	**all_path;
	char	**cmd;

	cmd = NULL;
	cmd = init_cmd(mini.tab, cmd);
	all_path = recup_path(mini);
	ft_exec(mini, all_path, cmd);
}
