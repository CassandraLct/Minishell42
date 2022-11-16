/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/16 16:31:03 by clecat           ###   ########.fr       */
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

//met copy exp a NULL
char	**init_exp(g_min mini)
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

//verifie si index envoyer est deja present dans copy exp
int	check_exp(g_min mini, int index)
{
	int	i  = 0;

	while(mini.exp_env[i])
	{
		if(strcmp(mini.c_env[index], mini.exp_env[i]) == 0)
			return(1);
		i++;
	}
	return(0);
}

int	tablen(g_min mini)
{
	int i = 0;
	int y = 0;

	while(mini.c_env[i])
		i++;
	printf("len c_env = %d\n", i);
	while(mini.exp_env[y])
		y++;
	printf("len exp_env = %d\n", y);
	if(y != i)
		return(1);
	return(0);
}

void	fill_exp(g_min mini, char *str)
{
	int i = 0;

	while(mini.exp_env[i])
		i++;
	mini.exp_env[i] = strdup(str);
	mini.exp_env[i + 1] = NULL;
}

void	export(g_min mini)
{
	int i = 0;
	int	index = 0;

	mini.exp_env = init_exp(mini);
	while(tablen(mini) != 0)
	{
		while(mini.c_env[i])
		{
			if (strcmp(mini.c_env[index], mini.c_env[i]) < 0 && check_exp(mini, i) == 0)
				index = i;
			i++;
		}
		fill_exp(mini, mini.c_env[index]); //fonction remplissage de exp
		i = 0;
	}
	i = 0;
	while(mini.exp_env[i])
	{
		printf("exp_env = %s, i = %d\n", mini.exp_env[i], i);
		i++;
	}
}
