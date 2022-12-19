/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:50 by clecat            #+#    #+#             */
/*   Updated: 2022/12/19 15:00:46 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 fonctions
void	ft_env(t_min mini)
{
	int	i;

	i = 1;
	if (mini.tab[i] != NULL)
	{
		printf("env: %s: No such file or directory\n", mini.tab[i]);
		return ;
	}
	else
	{
		i = 0;
		while (mini.c_env[i])
		{
			printf("%s\n", mini.c_env[i]);
			i++;
		}
	}
}

//change pwd env & exp with repo root
void	change_val(char **str, char *new_pwd)
{
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = 0;
	pwd = recup_pwd(str);
	oldpwd = recup_oldpwd(str);
	change_value_oldpwd(str, pwd, oldpwd);
	while(str[i])
	{
		if(ft_strncmp(str[i], "PWD=", 4) == 0)
			break;
		i++;
	}
	free(str[i]);
	str[i] = ft_strjoin("PWD=", new_pwd);
}
