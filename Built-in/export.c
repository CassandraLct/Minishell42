/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/18 16:21:19 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions
/*Pour export affiche que certaine
ecrit delare-x avant le nom de la variable, mets entre cote ce qu'il y a
après le =
affiche les variables par ordre ascii
export (qqc) sans égale s'affcihe que dans export
si = afficher aussi dans env

ne pas prendre des chiffres en param pour nom de variable 
bash-3.2$ export 42=a-b
bash: export: `42=a-b': not a valid identifier
bash-3.2$ export "42=a-b"
bash: export: `42=a-b': not a valid identifier*/

//print export with "declare-x" & valeur entre ""
void	print_export(t_min mini)
{
	int		i;
	int		y;
	int		index;

	i = 0;
	y = 0;
	while (mini.c_exp[i])
	{
		printf("declare -x ");
		while (mini.c_exp[i][y] != '=')
			printf("%c", mini.c_exp[i][y++]);
		printf("%c%c", mini.c_exp[i][y], 34);
		index = y + 1;
		while (mini.c_exp[i][index] != '\0')
			printf("%c", mini.c_exp[i][index++]);
		printf("%c\n", 34);
		y = 0;
		i++;
	}
}

//copy sur la derniere ligne d'env;
void	add_valenv(t_min mini, char *str)
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
	mini.c_env = ft_cptab(cpy);
}

//voir pour modifier check_exp
void	add_valexp(t_min mini, char *arg)
{
	char	**cpy;
	int		i;

	i = 0;
	while(mini.c_exp[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(mini.c_exp[i])
	{
		/*if(strncmp(mini.c_exp[i], arg, ft_strlen((void)arg)) == 0)
		{//checker valeur et si il faut modifier env aussi}*/
		if(strcmp(mini.c_exp[i], arg) > 0)
		{}
	}
}

//verifier si = present et quelque chose apres le =
//+25lignes
void	new_vars(t_min mini, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[0]) == 1)
		{
			printf("`%s': not a valid identifier\n", arg);
			exit(1);
		}
		if (arg[i] == '=')
		{
			if (arg[i + 1] == '\0') //a modifier (voir si gerer avec le lexer)
			{
				printf("cas 1: a copier que dans export: '%s'\n", arg);
				return ;
			}
			else
			{
				add_valenv(mini, arg);
				return ;
			}
		}
		i++;
	}
	printf("cas 3: a copie que dans export : '%s'\n", arg);
	return ;
}

//premiere partie d'export
//+25lignes
void	export(t_min mini)
{
	//char	*arg;
	int		i;
	int		index;

	i = 0;
	arg = "a42= bonjour";
	mini.c_exp = init_exp(mini.c_env);
	if (arg)
		new_vars(mini, arg);
	else
	{
		while (tablen(mini) != 0)
		{
			index = 0;
			while (check_exp(mini, index) != 0)
				index++;
			while (mini.c_env[i])
			{
				if (strcmp(mini.c_env[index], mini.c_env[i]) > 0
					&& check_exp(mini, i) == 0)
					index = i;
				i++;
			}
			fill_exp(mini, mini.c_env[index]);
			i = 0;
		}
		print_export(mini);
	}
}
