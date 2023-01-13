/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:50 by clecat            #+#    #+#             */
/*   Updated: 2023/01/13 18:19:11 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
void	ft_env(t_min *mini)
{
	int	i;

	i = 1;
	if (mini->tab[i] != NULL)
	{
		printf("env: %s: No such file or directory\n", mini->tab[i]);
		return ;
	}
	else
	{
		i = 0;
		while (mini->c_env[i])
		{
			printf("%s\n", mini->c_env[i]);
			i++;
		}
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

//cd et cd ~
void	cd_noarg(t_min *mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = recup_pwd(mini->c_env);
	oldpwd = recup_oldpwd(mini->c_env);
	change_val(mini->c_env, mini->val_home, pwd, oldpwd);
	change_val(mini->c_exp, mini->val_home, pwd, oldpwd);
	chdir(mini->val_home);
	free(pwd);
	free(oldpwd);
}
