/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:50 by clecat            #+#    #+#             */
/*   Updated: 2023/01/21 12:13:51 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions

int	verif_path(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (i == tablen(tab))
		return (1);
	return (0);
}

void	ft_env(t_min *mini, char **cmd)
{
	int	i;

	i = 1;
	if (verif_path(mini->c_env) == 1)
	{
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		mini->ret_err = 127;
		return ;
	}
	if (cmd[i] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[i]);
		mini->ret_err = 127;
		return ;
	}
	else
	{
		i = 0;
		while (mini->c_env[i])
			printf("%s\n", mini->c_env[i++]);
	}
}

//change pwd env & exp with repo root
void	change_val(char **str, char *new_pwd, char *pwd, char *oldpwd)
{
	int		i;

	i = 0;
	change_value_oldpwd(str, pwd, oldpwd);
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	free(str[i]);
	str[i] = ft_strjoin("PWD=", new_pwd);
}

//ajoute le nom du dossier a la fin
void	add_reponame(char **str, char *repo)
{
	char	*new_pwd;
	char	*all_addup;
	int		i;

	i = 0;
	new_pwd = NULL;
	while (str[i++])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
		{
			new_pwd = ft_strdup(str[i]);
			break ;
		}
	}
	free(str[i]);
	if (new_pwd[4] == '/' && new_pwd[5] == '\0')
		str[i] = ft_strjoin(new_pwd, repo);
	else
	{
		all_addup = ft_strjoin(new_pwd, "/");
		str[i] = ft_strjoin(all_addup, repo);
		free(all_addup);
	}
	free(new_pwd);
}
