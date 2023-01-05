/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:06:45 by clecat            #+#    #+#             */
/*   Updated: 2023/01/05 13:25:28 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//3 fonctions
//verifie si un . est present dans le fichier quand chdir return 1
int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

//recupere la valeur de pwd avant changement
char	*recup_pwd(char **str)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = NULL;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PWD=", 4) == 0)
		{
			pwd = ft_strdup(str[i]);
			break ;
		}
		i++;
	}
	return (pwd);
}

//recupere la valeur de oldpwd avant changement
char	*recup_oldpwd(char **str)
{
	char	*oldpwd;
	int		i;

	i = 0;
	oldpwd = NULL;
	while (str[i])
	{
		if (ft_strncmp(str[i], "OLDPWD=", 7) == 0)
		{
			oldpwd = ft_strdup(str[i]);
			break ;
		}
		i++;
	}
	return (oldpwd);
}

//join nom fonction & la nouvelle valeur;
char	*join_var(char *str1, char *new_val)
{
	char	*dest;
	char	*cpy;
	int		i;
	int		j;

//	i = 45;
	j = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(new_val) + 1));
	i = 0;
	while (new_val[i] != '=')
		i++;
//	if (new_val[i] == '=')
//	{
		i += 1;
		while (new_val[i])
			cpy[j++] = new_val[i++];
		cpy[j] = '\0';
//	}
	dest = ft_strjoin(str1, cpy);
	free(cpy);
	return (dest);
}

//modifie la valeur de oldpwd
void	cpy_value(char *name_var, char **str, char *new_val)
{
//	char	*s1;
	char	*ret;
	int		i;

	i = 0;
//	s1 = ft_strdup(name_var);
//	ret = join_var(s1, new_val);
//	free(s1);
	ret = join_var(name_var, new_val);
	while (str[i])
	{
		if (ft_strncmp(str[i], name_var, ft_strlen(name_var)) == 0)
		{
			free(str[i]);
			str[i] = ft_strdup(ret);
			break ;
		}
		i++;
	}
	free(ret);
}
