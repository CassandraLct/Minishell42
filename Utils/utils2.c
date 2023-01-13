/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:41 by clecat            #+#    #+#             */
/*   Updated: 2023/01/13 18:21:18 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//2 fonctions
int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] == s2[i])
		return (0);
	else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '	' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

char	*cd_tildpwd(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	
	i = 1;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while(str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	if(tmp[j - 1] == '/')
		tmp[j - 1] = '\0';
	else 
		tmp[j] = '\0';
	return(tmp);
}

void	cd_tildrepo(char **str, char *tab)
{
	char	*new_pwd;
	int	i;

	i = 0;
	new_pwd = cd_tildpwd(tab);
	while(str[i])
	{
		if(ft_strncmp(str[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	free(str[i]);
	str[i] = ft_strjoin("PWD=", g_mini.val_home);
	str[i] = ft_strjoin(str[i], new_pwd);
	free(new_pwd);
}

void	change_valcdtild(t_min *mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = recup_pwd(mini->c_env);
	oldpwd = recup_oldpwd(mini->c_env);
	if (ft_strcmp(mini->tab[1], "~/") > 0)
	{
		change_value_oldpwd(mini->c_env, pwd, oldpwd);
		change_value_oldpwd(mini->c_exp, pwd, oldpwd);
		cd_tildrepo(mini->c_env, mini->tab[1]);
		cd_tildrepo(mini->c_exp, mini->tab[1]);
		free(pwd);
		pwd = recup_pwd(mini->c_env);
		chdir(pwd);
	}
	else 
		cd_noarg(mini);
}
