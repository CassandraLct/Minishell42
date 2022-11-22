/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2022/11/22 11:29:18 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execve, perror, access
//voir si a modifier pour gerer les options
void	exec(t_min mini, char *argv)
{
	char	**all_path;
	char	*gd_path;
	char	*b_path;
	char	**cmd1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd1 = NULL;
	cmd1 = ft_split(argv, ' ');
	cmd1[0] = ft_strjoin("/", argv);
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
		gd_path = ft_strjoin(all_path[i], cmd1[0]);

		if (access(gd_path, R_OK) == 0)
		{
			printf("commande existante: %s\n", gd_path);
			if (execve(gd_path, cmd1, mini.c_env) == -1)
				perror("Execve : ");
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if(j == i)
		printf("minishell: %s: command not found\n", argv);
}
