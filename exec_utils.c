/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:04:33 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 11:03:47 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//3 fonctions
//recupe path pour fonction recup_path
char	*recup_pathexec(t_min *mini)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (mini->c_env[i])
	{
		if (ft_strncmp(mini->c_env[i], "PATH=", 5) == 0)
		{
			tmp = ft_strdup(mini->c_env[i] + 5);
			break ;
		}
		i++;
	}
	return (tmp);
}

int	verif_cmd(char **all_path, char **pathcmd, char **cmd)
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
			free(gd_path);
			return (0);
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if (j == i)
		return (aff_errcmd(cmd));
	return (0);
}

// bash-3.2$ cd./../
// bash: cd./../: No such file or directory
// bash-3.2$ bonjour
// bash: bonjour: command not found
int	aff_errcmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '/')
		{
			printf("minishell: %s: No such file or directory\n", cmd[0]);
			g_mini.ret_err = 127;
			return (g_mini.ret_err);
		}
		i++;
	}
	printf("minishell: %s: command not found\n", cmd[0]);
	g_mini.ret_err = 127;
	return (g_mini.ret_err);
}
