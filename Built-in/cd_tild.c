/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:59:22 by clecat            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:20 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//3 fonctions
//recupere le chemin donné apres le tild
char	*cd_tildpwd(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	if (tmp[j - 1] == '/')
		tmp[j - 1] = '\0';
	else
		tmp[j] = '\0';
	return (tmp);
}

void	change_valtab(t_min *mini)
{
	char	*tmp;

	tmp = cd_tildpwd(mini->tab[1]);
	free(mini->tab[1]);
	mini->tab[1] = ft_strjoin(g_mini.val_home, tmp);
	free(tmp);
}

//change le pwd
void	cd_tildrepo(char **str, char *tab)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	free(str[i]);
	str[i] = ft_strjoin("PWD=", tab);
}

void	change_valcdtild(t_min *mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = recup_pwd(mini->c_env);
	oldpwd = recup_oldpwd(mini->c_env);
	if (ft_strcmp(mini->tab[1], "~/") > 0)
	{
		change_valtab(mini);
		if (chdir(mini->tab[1]) == -1)
			aff_err();
		else
		{
			change_value_oldpwd(mini->c_env, pwd, oldpwd);
			change_value_oldpwd(mini->c_exp, pwd, oldpwd);
			cd_tildrepo(mini->c_env, mini->tab[1]);
			cd_tildrepo(mini->c_exp, mini->tab[1]);
			chdir(mini->tab[1]);
		}
	}
	else
		cd_noarg(mini);
	free(pwd);
	free(oldpwd);
}
