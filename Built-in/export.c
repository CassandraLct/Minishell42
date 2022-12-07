/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/12/07 12:01:07 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//4 fonctions
/*export (qqc) sans égale s'affiche que dans export
si = afficher aussi dans env
si var deja dans env et que la valeur est modifier, elle reste dans env mais
la val est bien changer*/

//faire remonter en faisant return return(mini)
//verifier si = present et quelque chose apres le =
//+25lignes (30 lignes) a revoir
t_min	new_vars(t_min mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (mini.tab[i])
	{
		while (mini.tab[i][j] != '\0')
		{
			if (ft_isdigit(mini.tab[i][0]) == 1)
			{
				printf("minishell: `%s': not a valid identifier\n", mini.tab[i]);
				exit(1);
			}
			if (mini.tab[i][j] == '=') //a remplacer par check_var
			{
				if (mini.tab[i][j + 1] != '\0')
				{
					mini.c_env = add_valenv(mini, mini.tab[i]);
					mini.c_exp = add_valexp(mini, mini.tab[i]);
					return (mini);
				}
			}
			j++;
		}
		i++;
		j = 0;
	}
	mini.c_exp = add_valexp(mini, mini.tab[1]);
	return(mini);
}

//verifie si index envoyer est deja present dans copy exp
//cmp = env ou cpy
int	check_exp(char **cmp, char **c_exp, int index)
{
	int	i;

	i = 0;
	if (!c_exp)
		return (0);
	while (c_exp[i])
	{
		if (strcmp(cmp[index], c_exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//trie export par ordre ascii
//cmp = c_env ou cpy
char	**order_exp(char **c_exp, char **cmp)
{
	int	index;
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (tablen(cmp) > y)
	{
		index = 0;
		while (check_exp(cmp, c_exp, index) != 0)
			index++;
		while (cmp[i])
		{
			if (strcmp(cmp[index], cmp[i]) > 0
				&& check_exp(cmp, c_exp, i) == 0)
				index = i;
			i++;
		}
		c_exp = fill_exp(c_exp, cmp[index]);
		i = 0;
		y++;
	}
	return (c_exp);
}

//add new_var ou affiche export
t_min	export(t_min mini)
{
	int	i;

	i = 1;
	if (mini.tab[1] == NULL)
		print_export(mini.c_exp);
	else
	{
		while (mini.tab[i] != NULL)
		{
			mini = new_vars(mini);
			i++;
		}
	}
	return(mini);
}
