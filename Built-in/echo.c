/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:37:12 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 11:23:02 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
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
	while (arg[i])
	{
		if (check_arg_opt(arg[i]) == 0)
		{
			print_arg_opt(arg, i);
			return (0);
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
	}
	return (0);
}

int	echo(char **arg)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!arg[1])
	{
		printf("\n");
		return (0);
	}
	else if (arg[1][0] == 45)
		check_opt(arg);
	while (arg[i] && (arg[i][j] >= 33 && arg[i][j] <= 126) && arg[i][0] != 45)
	{
		if (arg[i + 1] == NULL)
			printf("%s\n", arg[i]);
		else
			printf("%s ", arg[i]);
		i++;
	}
	return (0);
}
