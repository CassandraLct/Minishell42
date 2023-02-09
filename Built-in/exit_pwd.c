/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2023/02/09 10:48:10 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions

void	change_val_pwdpath(char **str, char **cmd)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(cmd[1], '/');
	while (path[i])
	{
		if (ft_strcmp(path[i], "..") == 0)
			change_value_pwd(str);
		if (ft_strcmp(path[i], "..") != 0 && ft_strcmp(path[i], ".") != 0)
			add_reponame(str, path[i]);
		i++;
	}
	free_tab(path);
}

//remonte un fichier au_dessus pour avoir le new_pwd;
int	recup_new_pwd(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
		{
			while (str[i][j] != '\0')
				j++;
			if (str[i][j] == '\0')
				break ;
		}
		i++;
	}
	while (str[i][j] != '/')
		j--;
	return (j);
}

//affiche le pwd (voir si modifier lors du changement)
void	pwd(char **c_env, char **cmd)
{
	int	i;

	i = 0;
	while (c_env[i])
	{
		if (ft_strncmp(c_env[i], "PWD=", 4) == 0)
		{
			while (c_env[i])
			{
				printf("%s\n", c_env[i] + 4);
				return ;
			}
		}
		i++;
	}
	if (i == tablen(c_env))
	{
		g_mini.ret_err = 127;
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		return ;
	}
}

// la fonction sort de minishell ou redirige vers la verif des arguments
void	exit_min(t_min *mini, char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (mini->struct_cmd[j])
		j++;
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (cmd[i] == NULL)
		{
			if (j == 1)
				printf("exit\n");
			exit(0);
		}
		else
			verif_arg_exit(mini, i, cmd);
	}
}
