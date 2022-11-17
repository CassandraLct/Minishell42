/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 15:27:29 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

/*Pour export affiche que certaine
ecrit delare-x avant le nom de la variable, mets entre cote ce qu'il y a
après le =
affiche les variables par ordre ascii
export (qqc) sans égale s'affcihe que dans export
si = afficher aussi dans env*/

//print export with "declare-x" & valeur entre ""
void	print_export(t_min mini)
{
	int i;
	int y;
	int index;
	char c;

	i = 0;
	y = 0;
	c = 34;
	while (mini.c_exp[i])
	{
		printf("declare -x ");
		while(mini.c_exp[i][y] != '=')
		{
			printf("%c", mini.c_exp[i][y]);
			y++;
		}
		printf("%c%c", mini.c_exp[i][y], c);
		index = y + 1;
		while (mini.c_exp[i][index] != '\0')
		{
			printf("%c", mini.c_exp[i][index]);
			index++;
		}
		printf("%c\n", c);
		y = 0;
		i++;
	}
}

//verifie si index envoyer est deja present dans copy exp
int	check_exp(t_min mini, int index)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
	{
		if (strcmp(mini.c_env[index], mini.c_exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//compare la taille des 2
int	tablen(t_min mini)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (mini.c_env[i])
		i++;
	while (mini.c_exp[y])
		y++;
	if (y != i)
		return (1);
	return (0);
}

//copie env ds exp dans l'ordre ascii
void	fill_exp(t_min mini, char *str)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
		i++;
	mini.c_exp[i] = ft_strdup(str);
	mini.c_exp[i + 1] = NULL;
}

//premiere partie d'export
void	export(t_min mini)
{
	int	i;
	int	index;

	i = 0;
	mini.c_exp = init_cpy(mini.c_env, mini.c_exp);
	while (tablen(mini) != 0)
	{
		index = 0;
		while (check_exp(mini, index) != 0)
			index++;
		while (mini.c_env[i])
		{
			if (strcmp(mini.c_env[index], mini.c_env[i]) > 0 && check_exp(mini, i) == 0)
				index = i;
			i++;
		}
		fill_exp(mini, mini.c_env[index]);
		i = 0;
	}
	print_export(mini);
}
