/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:52:33 by clecat            #+#    #+#             */
/*   Updated: 2022/11/03 19:00:19 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//bien comprendre les chevrons, les redirections et les pipes(surtout dup)
//recuperer et stocker l'env, faire echo, exit et pwd
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	pwd(char **c_env)
{
	int i = 0;
	int j = 5;
	
	while(c_env[i])
	{
		if(strncmp(c_env[i], "PWD=", 4) == 0)
		{
			while(c_env[i])
				return(printf("%s\n", c_env[i] + 4));
		}
		i++;
	}
}

void	recup_env(char **env)
{
	char	**c_env;
	int i = 0;
	int y = 0;
	int x = 0;
	
	while(env[i])
		i++;
	c_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(env[i])
	{
		while(env[i][y] != '\0')
			y++;
		c_env[x] = malloc(sizeof (char) * y + 1);
		x++;
		y = 0;
		i++;
	}
	i = 0;
	y = 0;
	x = 0;
	while(env[i] && c_env[x])
	{
		while(env[i][y] != '\0')
		{
			c_env[x][y] = env[i][y];
			y++;
		}
		c_env[x][y] = '\0';
		x++;
		i++;
		y = 0;
	}
	c_env[x] = NULL;
	/*x = 0;
	while(c_env[x])
	{
		printf("%s\n", c_env[x]);
		x++;
	}*/
	pwd(c_env);
}

int strdigit(char *str)
{
	int i = 0;
	int y = 0;

	while (str[y])
	{
		if(str[y] >= '0' && str[y] <= '9')
			i++;
		y++;
	}
	if (i != y)
		return(1);
	return(0);
}

// exit doit avoir 0 ou 1 arg, qui doit etre numerique
void    exit_min(char **argv)
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
					//code retour a mettre a (1);
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

int main(int argc, char **argv, char **env)
{
	argc = 1;
	argv[1] = "exit";
	argv[2] = "213";
	argv[3] = NULL;
	//argv[4] = NULL;
	/*char **str;
	str[0] = "patate";
	str[1] = "exit";
	str[2] = "1234";
	str[3] = NULL;*/
	//recup_env(env);
	exit_min(argv);
}
