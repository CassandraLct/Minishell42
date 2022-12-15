/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:55:50 by clecat            #+#    #+#             */
/*   Updated: 2022/12/15 16:41:08 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
//change la valeur de pwd
void	change_value_pwd(char **str)
{
	char	*new_val;
	int		i;
	int		j;
	int		w;

	i = 0;
	j = 0;
	w = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	j = recup_new_pwd(str);
	new_val = malloc(sizeof(char) * (j + 1));
	while (str[i][w] && w < j)
	{
		new_val[w] = str[i][w];
		w++;
	}
	new_val[w] = '\0';
	free(str[i]);
	str[i] = ft_strdup(new_val);
	free(new_val);
	printf("str[i] = %s\n",str[i]);
}

//change la valeur de oldpwd
void	change_value_oldpwd(char **str, char *pwd, char *oldpwd)
{
	char	*name_var;
	int		j;
	int		i;
	int		y;

	j = 0;
	i = 0;
	y = 0;
	while (oldpwd[j++] != '=')
		y++;
	if (j != ft_strlen(oldpwd))
		j++;
	name_var = malloc(sizeof(char) * (y + 2));
	while (i < y)
	{
		name_var[i] = oldpwd[i];
		i++;
	}
	name_var[i] = '=';
	name_var[i + 1] = '\0';
	cpy_value(name_var, str, pwd);
	free(name_var);
	free(oldpwd);
}

//modifie env (pwd et oldpwd) en fonction du path donner
void	change_value_env(t_min mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = recup_pwd(mini.c_env);
	oldpwd = recup_oldpwd(mini.c_env);
	if (strcmp(mini.tab[1], ".") == 0 || strcmp(mini.tab[1], "./") == 0)
		change_value_oldpwd(mini.c_env, pwd, oldpwd);
	else if (strcmp(mini.tab[1], "..") == 0 || strcmp(mini.tab[1], "../") == 0)
	{
		printf("retourne au reportoire au-dessus, env\n");
		change_value_pwd(mini.c_env);
		change_value_oldpwd(mini.c_env, pwd, oldpwd);
	}
	else if (strcmp(mini.tab[1], ".") > 0 || strcmp(mini.tab[1], "..") > 0)
	{
		printf("va au chemin indiqué, env\n");
		change_value_oldpwd(mini.c_env, pwd, oldpwd);
		change_val_pwdpath(mini, mini.c_env);
	}
	free(pwd);
}

//modifie exp (pwd et oldpwd) en fonction du path donner
void	change_value_exp(t_min mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = recup_pwd(mini.c_exp);
	oldpwd = recup_oldpwd(mini.c_exp);
	if (strcmp(mini.tab[1], ".") == 0 || strcmp(mini.tab[1], "./") == 0)
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
	else if (strcmp(mini.tab[1], "..") == 0 || strcmp(mini.tab[1], "../") == 0)
	{
		printf("retourne au reportoire au-dessus, exp\n");
		change_value_pwd(mini.c_exp);
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
	}
	else if (strcmp(mini.tab[1], "./") > 0 || strcmp(mini.tab[1], "../") > 0)
	{
		printf("va au chemin indiqué, exp\n");
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
		//change_val_pwdpath(mini, mini.c_exp);
	}
	free(pwd);
}

//1er if change oldpwd, 2e if change les 2 pwd, 3e if les 2 pwd
//cd sans arg return, fichier non existant, si 2 arg -> ne prend pas en compte le deuxieme
//cas specifique a verifier: si repo au dessus est supprimer, et que cd .. est fait ->doit afficher une erreur
void	cd(t_min mini)
{
	if (mini.tab[1] == NULL)
		return ;
	if (chdir(mini.tab[1]) == -1)
	{
		if (check_arg(mini.tab[1]) == 1)
			printf("minishell: cd: %s: Not a directory\n", mini.tab[1]);
		else
		{
			printf("minishell: cd: %s:", mini.tab[1]);
			printf("No such file or directory\n");
		}
	}
	else
	{
		change_value_env(mini);
		change_value_exp(mini);
	}
}
