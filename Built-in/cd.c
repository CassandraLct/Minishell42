/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:55:50 by clecat            #+#    #+#             */
/*   Updated: 2022/11/18 18:07:19 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_value_pwd(t_min mini, char *pwd, char *oldpwd)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (pwd[i] != '=')
		i++;
	while (oldpwd[j] != '=')
		j++;
	printf("i = %d, j = %d\n", i, j);
	if(strcmp(&pwd[i], &oldpwd[j]) != 0) //a modifier
	{
		printf("change value oldpwd, %s\n", mini.cdpath);
	}
}

void	recup_value_pwd(t_min mini)
{
	char	*pwd;
	char	*oldpwd;
	int		i;
	
	i = 0;
	while(mini.c_env[i])
	{
		if(ft_strncmp(mini.c_env[i], "PWD=", 4) == 0)
			pwd = mini.c_env[i];
		i++;
	}
	i = 0;
	while(mini.c_env[i])
	{
		if(ft_strncmp(mini.c_env[i], "OLDPWD=", 7) == 0)
			oldpwd = mini.c_env[i];
		i++;
	}
	change_value_pwd(mini, pwd, oldpwd);
	//printf("pwd = %s\noldpwd = %s\n", pwd, oldpwd);
}

//utiliser chdir
//pour cd . voir le comportement exact
void	cd(t_min mini)
{
	if(chdir(mini.cdpath) == -1)
		printf("bash: cd: %s: No such file or directory\n", mini.cdpath);
	else
	{
		if (strcmp(mini.cdpath, ".") == 0)
		{
			printf("ne change pas de repertoire\n");
			//change le oldpwd sauf si deja egal
			recup_value_pwd(mini);
		}
		if (strcmp(mini.cdpath, "..") == 0)
		{
			printf("retourne au reportoire au-dessus\n");
			//change le pwd et le oldpwd
		}
		if(strcmp(mini.cdpath, ".") > 0 || strcmp(mini.cdpath, "..") > 0)
		{
			printf("va au chemin indiqué\n");
		}
	}
}