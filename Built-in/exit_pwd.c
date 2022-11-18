/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2022/11/18 08:59:31 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//2 fonctions
//affiche le pwd
void	pwd(char **c_env)
{
	int	i;

	i = 0;
	while (c_env[i])
	{
		if (strncmp(c_env[i], "PWD=", 4) == 0)
		{
			while (c_env[i])
				printf("%s\n", c_env[i] + 4);
		}
		i++;
	}
}

void	aff_err(char *proc, char *fonct, char *arg, char *err)
{
	//a faire autrement
}

// exit doit avoir 0 ou 1 arg, qui doit etre numerique
//a modifier en fonction du lexer fonction +25lignes (faire fonction aff_error); 
//strcmp a faire
void	exit_min(char **argv, t_min mini)
{
	int	i;

	i = 2;
	if (strcmp(argv[1], "exit") == 0)
	{
		if (argv[i] == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		while (argv[i])
		{
			if (strdigit(argv[i]) == 0)
			{
				if (argv[i + 1] == NULL)
				{
					printf("exit\n");
					exit(atoi(argv[i]) % 256);
				}
				else
				{
					printf("exit\n");
					printf("minishell: exit : too many arguments\n");
					mini.ret_err = 1;
				}
			}
			else if (strdigit(argv[i]) == 1)
			{
				printf("exit\n");
				printf("minishell: exit: %s: numeric argument required\n", argv[i]); //ligne trop longue
				exit(255);
			}
			break ;
		}
	}
}
