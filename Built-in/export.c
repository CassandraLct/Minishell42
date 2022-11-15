/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/15 16:37:28 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

/*Pour export affiche que certaine 
ecrit delare-x avant le nom de la variable, mets entre cote ce qu'il y a après le =
affiche les variables par ordre ascii
export (qqc) sans égale s'affcihe que dans export
si = afficher aussi dans env*/

//apprendre a utiliser realloc
char	**copy_env(g_min mini)
{
	int i = 0;
	
	while(mini.c_env[i])
		i++;
	mini.exp_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(mini.exp_env[i])
	{
		mini.exp_env[i] = NULL;
		i++;
	}
	mini.exp_env[i] = NULL;
	return(mini.exp_env);
}

int	check_exp(g_min mini, int index)
{
	int	i  = 0;
	int x = 0;
	int y = 0;
	
	printf("check_exp\n");
	if(!mini.exp_env[0])
	{
		printf("if exp_env vide\n");
		mini.exp_env[0] = malloc(sizeof(char) * strlen(mini.c_env[index]) + 1);
		while(mini.c_env[index][y] != '\0')
		{
			mini.exp_env[0][y] = mini.c_env[index][y];
			y++;
		}
		mini.exp_env[x][y] = '\0';
		return(0);
	}
	else
	{
		printf("else\n");
		y = 0;
		while(mini.exp_env[i])
		{
			if(strcmp(mini.c_env[index], mini.exp_env[i]) == 0)
				return(1);
			else
			{
				mini.exp_env[i + 1] = malloc(sizeof(char) * strlen(mini.c_env[index]));
				while(mini.c_env[index][y] != '\0')
				{
					mini.exp_env[i + 1][y] = mini.c_env[index][y];
					y++;
				}
				mini.exp_env[i + 1][y] = '\0';
			}
			i++;
		}
	}
	return(0);
}

void	export(g_min mini)
{
	int i = 0;
	int y = 0;
	int	index = 0;
	
	mini.exp_env = copy_env(mini);
	while(mini.c_env[i])
	{
		if (strcmp(mini.c_env[index], mini.c_env[i]) > 0)
			index = i;
		i++;
	}
	if(check_exp(mini, index) == 0)
	{
		printf("%s\n", mini.exp_env[y]);
		//export(mini);
	}
	else if(check_exp(mini, index) != 0)
		export(mini);
}
