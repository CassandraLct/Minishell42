/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:37:12 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 11:21:12 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//4 fonctions
//verifie si que des n pour l'option (0) sinon (1)
int	check_arg_opt(char *arg)
{
	int	i;

	i = 1;
	if (!arg[i])
		return (1);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
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
		while (arg[i] && check_arg_opt(arg[i]) == 0)
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
	return (0);
}

//verifie si echo a des arguments ou non
void	echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd[1] == NULL || cmd[1][0] == '\0')
		printf("\n");
	else if (cmd[i][0] == '-')
		check_opt(cmd);
	else
	{
		while (cmd[i] && cmd[i][0] != '\0' && (cmd[i][j] >= 32
			&& cmd[i][j] <= 126))
		{
			if (cmd[i + 1] == NULL)
				printf("%s\n", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
	g_mini.ret_err = 0;
	return ;
}

void	echo2(char **cmd)
{
	int	i;
	int	is_option;
	int	after_option;

	i = 1;
	is_option = 0;
	after_option = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && check_arg_opt(cmd[i]) == 0 && after_option == 0)
			is_option = 1;
		else
		{
			after_option = 1;
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
		}
		i++;
	}
	if (is_option == 0)
		printf("\n");
	g_mini.ret_err = 0;
	return ;
}
