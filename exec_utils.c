/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:04:33 by clecat            #+#    #+#             */
/*   Updated: 2023/01/19 16:30:41 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//2 fonctions
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

int	verif_cmd(char **all_path, char **cmd)
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
			return(0);
		}
		else
			j++;
		free(gd_path);
		i++;
	}
	if (j == i)
		return(aff_errcmd());
	return (0);
}

int	aff_errcmd(void)
{
	g_mini.ret_err = 127;
	printf("minishell: %s: command not found\n", g_mini.tab[0]);
	return (-1);
}
