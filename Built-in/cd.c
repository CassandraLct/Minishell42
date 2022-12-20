/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:55:50 by clecat            #+#    #+#             */
/*   Updated: 2022/12/20 10:49:26 by clecat           ###   ########.fr       */
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
	if (mini.tab[1][0] == '/')
		change_val(mini.c_env, mini.tab[1]);
	if (strcmp(mini.tab[1], ".") == 0 || strcmp(mini.tab[1], "./") == 0)
		change_value_oldpwd(mini.c_env, pwd, oldpwd);
	else if (strcmp(mini.tab[1], "..") == 0 || strcmp(mini.tab[1], "../") == 0)
	{
		change_value_pwd(mini.c_env);
		change_value_oldpwd(mini.c_env, pwd, oldpwd);
	}
	else if ((strcmp(mini.tab[1], "./") > 0 || strcmp(mini.tab[1], "../") > 0))
	{
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
	if (mini.tab[1][0] == '/')
		change_val(mini.c_exp, mini.tab[1]);
	else if (strcmp(mini.tab[1], ".") == 0 || strcmp(mini.tab[1], "./") == 0)
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
	else if (strcmp(mini.tab[1], "..") == 0 || strcmp(mini.tab[1], "../") == 0)
	{
		change_value_pwd(mini.c_exp);
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
	}
	else if (strcmp(mini.tab[1], "./") > 0 || strcmp(mini.tab[1], "../") > 0)
	{
		change_value_oldpwd(mini.c_exp, pwd, oldpwd);
		change_val_pwdpath(mini, mini.c_exp);
	}
	free(pwd);
}

//redirige vers les fonction adéquat
void	cd(t_min mini)
{
	char	*str;

	str = "/Users/clecat";
	if (mini.tab[1] == NULL)
	{
		printf("reviens au repo racine\n");
		change_val(mini.c_env, str);
		change_val(mini.c_exp, str);
		chdir("/Users/clecat");
	}
	else if (chdir(mini.tab[1]) == -1)
	{
		if (check_arg(mini.tab[1]) == 1)
			printf("minishell: cd: %s: Not a directory\n", mini.tab[1]);
		else
		{
			printf("minishell: cd: %s: ", mini.tab[1]);
			printf("No such file or directory\n");
		}
	}
	else
	{
		change_value_env(mini);
		change_value_exp(mini);
	}
}
