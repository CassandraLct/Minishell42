/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:55:50 by clecat            #+#    #+#             */
/*   Updated: 2022/12/06 11:33:55 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5fonctions
char	*join_var(char *str1, char *new_val)
{
	char	*dest;
	char	*cpy;
	int		i;
	int		j;

	i = 45;
	j = 0;
	cpy = malloc(sizeof(char) * i);
	i = 0;
	while (new_val[i] != '=')
		i++;
	if (new_val[i] == '=')
	{
		i += 1;
		while (new_val[i])
			cpy[j++] = new_val[i++];
		cpy[j] = '\0';
	}
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(cpy) + 1));
	dest = ft_strjoin(str1, cpy);
	return (dest);
}

//a modifier pour etre utiliser pour tout les cas
void	cpy_value(char **str, char *new_val)
{
	char	*s1;
	char	*ret;
	int		i;

	i = 0;
	s1 = ft_strdup("OLDPWD=");
	ret = join_var(s1, new_val);
	while (str[i])
	{
		if (strncmp(str[i], "OLDPWD=", 7) == 0)
			str[i] = ft_strdup(ret);
		i++;
	}
}

//
void	change_value_pwd(t_min mini, char **str, char *pwd, char *oldpwd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("str = %s\n", str[i]);
	while (pwd[i] != '=')
		i++;
	while (oldpwd[j] != '=')
		j++;
	printf("change value oldpwd, %s\n", mini.cdpath);
	cpy_value(str, pwd);
}

//recuperation des valeurs de PWD et OLDPWD
void	recup_value_pwd(t_min mini, char **str)
{
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
			pwd = str[i];
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "OLDPWD=", 7) == 0)
			oldpwd = str[i];
		i++;
	}
	printf("ret _error = %d\n", mini.ret_err);
	change_value_pwd(mini, str, pwd, oldpwd);
}

//1er if change oldpwd, 2e if change les 2 pwd, 3e if les 2 pwd
//faire les autres cas plus tard
//cd sans arg return, fichier non existant
//(bash: cd: bonjour: No such file or directory)
//cd fichier : bash: cd: exec.c: Not a directory
//a modifier en fonction du tableau
void	cd(t_min mini)
{
	if (mini.cdpath == NULL)
		return ;
	if (chdir(mini.cdpath) == -1)
		printf("bash: cd: %s: No such file or directory\n", mini.cdpath);
	else
	{
		if (strcmp(mini.cdpath, ".") == 0)
		{
			recup_value_pwd(mini, mini.c_env);
			recup_value_pwd(mini, mini.c_exp);
		}
		if (strcmp(mini.cdpath, "..") == 0)
		{
			printf("retourne au reportoire au-dessus,change pwd et old\n");
		}
		if (strcmp(mini.cdpath, ".") > 0 || strcmp(mini.cdpath, "..") > 0)
		{
			printf("va au chemin indiqué,change pwd et old\n");
		}
	}
}
