/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:31 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 19:02:07 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execve, perror, access
//verifier que la commande existe split le path pour mettre la cmd a la fin
//voir pipex
void	exec(t_min mini, char **cmd)
{
	char	**all_path;
	char	*gd_path;
	char	*b_path;
	char	*cmd1;
	int		i;

	i = 0;
	cmd1 = ft_strjoin("/", cmd[1]);
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
		gd_path = ft_strjoin(all_path[i], cmd1);
		if (access(gd_path, R_OK) == 0)
		{
			printf("commande existante: %s\n", gd_path);
			if (execve(gd_path, &cmd1, mini.c_env) == -1)
				perror("Execve : ");
				// c2r4p9% ./minishell grep erreur rendu
				// commande existante: /usr/bin/grep
				// grep: .: Is a directory
		}
		free(gd_path);
		i++;
	}
	/*i = 0;
	while(all_path[i])
		printf("all_path = %s, cmd = %s\n", all_path[i++], cmd[1]);*/
}
