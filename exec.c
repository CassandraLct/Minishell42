/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2022/11/23 18:38:12 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execve, perror, access
//a gerer avec un fork pour empecher de sortir de minishell
//+25 lignes
void	exec(t_min mini)
{
	char	**all_path;
	char	*gd_path;
	char	*b_path;
	char	**cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = NULL;
	cmd = init_cpy(mini.tab, cmd);
	cmd = ft_cpytab(mini.tab);
	cmd[0] = ft_strjoin("/", cmd[0]);
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], "PATH=", 5) == 0)
			b_path = ft_strdup(mini.c_env[i] + 5);
		i++;
	}
	i = 0;
	all_path = ft_split(b_path, ':');
	while (all_path[i])
	{
		gd_path = ft_strjoin(all_path[i], cmd[0]);
		if (access(gd_path, R_OK) == 0)
		{
			printf("commande existante: %s\n", gd_path);
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
