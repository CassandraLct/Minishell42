/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:37:12 by clecat            #+#    #+#             */
/*   Updated: 2022/11/23 18:40:06 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//4 fonctions
/*echo sans arg affiche une ligne vide puis le prompt ok (a faire avec le
vraie prompt)
echo (num/string) affiche la string ok
echo -n n'affiche pas la nouvelle ligne (verif avec vraie minishell)
echo -n-n-n-n-n-n affiche le -n-n-n-... ok
echo -nnnnnnn même comportement que -n ok
echo -nnnnn5nnnn affiche -nnnnn5nnnn ok
echo $PATH ou "$PATH" affiche /Users/clecat/.brew/bin:/Users/clecat/... lexer
echo '$PATH' affiche $PATH lexer
echo $ affiche $ sur new line puis prompt sur new line (gerer par la string)
echo $? affiche la valeur lexer */

//verifie si que des n pour l'option
int	check_arg_opt(char *arg)
{
	int	i;
	int	y;

	i = 1;
	y = 1;
	while (arg[i])
	{
		if (arg[i] == 'n')
			y++;
		i++;
	}
	if (y != i)
		return (1);
	return (0);
}

//print les args option valide
int	print_arg_opt(char **arg, int i)
{
	if (arg[i + 1] == NULL)
		return (0);
	else if (arg[i + 1] != NULL)
	{
		i += 1;
		while (arg[i] != NULL)
		{
			if (arg[i + 1] == NULL)
				printf("%s", arg[i]);
			else
				printf("%s ", arg[i]);
			i++;
		}
	}
	return (1);
}

//verifie l'option
int	check_opt(char **arg)
{
	int	i;

	i = 1;
	if (check_arg_opt(arg[i]) == 0)
	{
		i++;
		while (arg[i] != NULL)
		{
			if (arg[i + 1] == NULL)
				printf("%s", arg[i]);
			else
				printf("%s ", arg[i]);
			i++;
		}
		/*print_arg_opt(arg, i);
		return (0);*/
	}
	else if (check_arg_opt(arg[i]) == 1)
	{
		while (arg[i])
		{
			if (arg[i + 1] == NULL)
				printf("%s\n", arg[i]);
			else
				printf("%s ", arg[i]);
			i++;
		}
	}
	return (0);
}

//verifie si echo a des arguments ou non
void	echo(t_min mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (strcmp(mini.tab[0], "echo") == 0)
	{
		if (!mini.tab[1])
		{
			printf("\n");
			return ;
		}
		else if (mini.tab[1][0] == 45)
			check_opt(mini.tab);
		while (mini.tab[i] && (mini.tab[i][j] >= 33 && mini.tab[i][j] <= 126)
			&& mini.tab[i][0] != 45)
		{
			if (mini.tab[i + 1] == NULL)
				printf("%s\n", mini.tab[i]);
			else
				printf("%s ", mini.tab[i]);
			i++;
		}
	}
	return ;
}
