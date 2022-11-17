/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:24 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 16:41:29 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//2 fonctions
//malloc la taille du tableau
char	**init_cpy(char **str, char **dest)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	dest = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (dest[i])
	{
		dest[i] = NULL;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

//copie de l'environnement + malloc de c_env
//fonction +25 lignes
char	**recup_env(char **env, t_min mini)
{
	int	i;

	i = 0;
	mini.c_env = init_cpy(env, mini.c_env);
	while (env[i])
	{
		mini.c_env[i] = ft_strdup(env[i]);
		i++;
	}
	mini.c_env[i] = NULL;
	return (mini.c_env);
}
