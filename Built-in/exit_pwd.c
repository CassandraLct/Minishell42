/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2022/11/15 11:05:16 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//affiche le pwd
void	pwd(char **c_env)
{
	int i = 0;
	//int j = 5;
	
	while(c_env[i])
	{
		if(strncmp(c_env[i], "PWD=", 4) == 0)
		{
			while(c_env[i])
				printf("%s\n", c_env[i] + 4);
		}
		i++;
	}
}

// exit doit avoir 0 ou 1 arg, qui doit etre numerique
//a modifier en fonction du lexer
void    exit_min(char **argv, g_min mini)
{
	int i = 2;
	
	if(strcmp(argv[1], "exit") == 0)
	{
		if(argv[i] == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		while(argv[i])
		{
			if(strdigit(argv[i]) == 0)
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
					mini.ret_error = 1;
				}
			}
			else if(strdigit(argv[i]) == 1)
			{
				printf("exit\n");
				printf("minishell: exit: %s: numeric argument required\n", argv[i]);
				exit(255);
			}
			break;
		}
	}
}

//segfault
/*void	env(g_min mini)
{
	int x = 0;

	x = 0;
	while(mini.c_env[x])
	{
		printf("%s\n", mini.c_env[x]);
		x++;
	}
}*/