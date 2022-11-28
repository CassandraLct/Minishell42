/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/28 16:39:21 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions
/*export (qqc) sans égale s'affiche que dans export
si = afficher aussi dans env
si var deja dans env et que la valeur est modifier, elle reste dans env mais
la val est bien changer*/

//copy sur la derniere ligne d'env;
char	**add_valenv(t_min mini, char *str)
{
	int		i;
	char	**cpy;

	i = 0;
	while (mini.c_env[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (mini.c_env[i])
	{
		cpy[i] = ft_strdup(mini.c_env[i]);
		i++;
	}
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = NULL;
	free_tab(mini.c_env);
	mini.c_env = ft_cpytab(cpy);
	return (mini.c_env);
}

//ajoute la variable dans export
//regler le probleme de malloc et de segfault
char	**add_valexp(t_min mini, char *str)
{
	char	**cpy;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (mini.c_exp[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (mini.c_exp[i])
	{
		cpy[i] = ft_strdup(mini.c_exp[i]);
		i++;
	}
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = NULL;
	while(cpy[y])
	{
		printf("cpy[%d] = %s\n", y, cpy[y]);
		y++;
	}
	free_tab(mini.c_exp);
	mini.c_exp = malloc(sizeof(char *) * (y + 1));
	//remplir c_exp de NULL;
	order_exp(mini, mini.c_exp, cpy);
	return (mini.c_exp);
}

//trie export par ordre ascii
//cmp = c_env ou cpy
void	order_exp(t_min mini, char **c_exp, char **cmp)
{
	int	index;
	int	i;

	i = 0;
	printf("cmp = %s\n", cmp[0]);
	while (tablen(cmp, c_exp) != 0)
	{
		printf("test\n");
		index = 0;
		while (check_exp(cmp, c_exp, index) != 0)
			index++;
		printf("test2\n");
		while (cmp[i])
		{
			//printf("dans boucle cmp, i = %d, ret = %d\n", i, strcmp(cmp[index], cmp[i]));
			if (strcmp(cmp[index], cmp[i]) > 0
				&& check_exp(cmp, c_exp, i) == 0)
				index = i;
			i++;
			printf("apres le if\n");
		}
		//printf("vers fill_exp, cmp[in] = %s\n", cmp[index]);
		fill_exp(mini, cmp[index]);
		i = 0;
	}
	printf("sortie\n");
}

//verifier si = present et quelque chose apres le =
void	new_vars(t_min mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (mini.tab[i])
	{
		while (mini.tab[i][j] != '\0')
		{
			if (ft_isdigit(mini.tab[1][0]) == 1)
			{
				printf("minishell: `%s': not a valid identifier\n", mini.tab[i]);
				exit(1);
			}
			if (mini.tab[i][j] == '=')
			{
				if (mini.tab[i][j + 1] == '\0')
					printf("cas 1: a copier que dans export: '%s'\n", mini.tab[i]);
				else
				{
					printf("copie dans env et export\n");
					mini.c_env = add_valenv(mini, mini.tab[i]);
					return ;
				}
			}
			j++;
		}
		i++;
		j = 0;
	}
	printf("cas 3: a copie que dans export : '%s'\n", mini.tab[1]);
	mini.c_exp = add_valexp(mini, mini.tab[1]);
}

//add new_var ou affiche export
void	export(t_min mini)
{
	if (mini.tab[1] != NULL)
		new_vars(mini);
	else
		print_export(mini.c_exp);
}
