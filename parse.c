/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:24 by clecat            #+#    #+#             */
/*   Updated: 2022/11/15 13:00:07 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//copie de l'environnement + malloc de c_env
//a mettre a la norm
char	**recup_env(char **env, g_min mini)
{
	int i = 0;
	int y = 0;
	int x = 0;
	
	while(env[i])
		i++;
	mini.c_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(env[i])
	{
		while(env[i][y] != '\0')
			y++;
		mini.c_env[x] = malloc(sizeof (char) * y + 1);
		x++;
		y = 0;
		i++;
	}
	i = 0;
	y = 0;
	x = 0;
	while(env[i] && mini.c_env[x])
	{
		while(env[i][y] != '\0')
		{
			mini.c_env[x][y] = env[i][y];
			y++;
		}
		mini.c_env[x][y] = '\0';
		x++;
		i++;
		y = 0;
	}
	mini.c_env[x] = NULL;
	return(mini.c_env);

}
