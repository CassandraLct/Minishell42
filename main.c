/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/23 18:17:38 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et puis checker premier arg si c'est une commande

t_min	g_mini;

//test
/*void	check_line(t_min mini)
{
	int	i;

	i = 0;
	while(mini.line[i])
	{
		while (mini.line[i] == 32 || mini.line[i] == '\t')
		{
			if(mini.line[i + 1] == '\0')
				return ;
			i++;
		}
		if (mini.line[i] == 34 || mini.line[i] == 39)
			printf("gestions des cotes\n");
		if (mini.line[i] == '|')
			printf("gestions des pipes\n");
		if (mini.line[i] == '-')
			printf("gestions option\n");
		if(mini.line[i] == '>' || mini.line[i] == '<')
			printf("gestions chevrons\n");
		else
			printf("autre cas\n");
		i++;
	}
}*/

//a finir (ne gere pas encore les cotes)
char	**split_line(t_min mini)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(mini.line[i])
	{
		if(mini.line[i] == 34 || mini.line[i] == 39)
		{
			c = mini.line[i];
			printf("c = %c\n", c);
			while(mini.line[i] != 34 || mini.line[i] != 39)
			{
				if(mini.line[i] != 34 && mini.line[i] != 39 
					&& mini.line[i + 1] == '\0')
					printf("minishell: `%s': cote not closed\n", mini.line);
				if (mini.line[i] == c)
				{
					printf("c= %c, line[i] = %c\n", c, mini.line[i]);
					printf("a copier dans le tableau, %s\n", mini.line);
				}
				j++;
				i++;
			}
		}
		i++;
	}
	if(j == 0)
		mini.tab = ft_split(mini.line, ' ');
	return(mini.tab);
}

//probleme a regler: valeur modifier non remonter, probleme avec l'historique
//modifier le split de la line
//faire fonction de redirection: soit vers les built-in, soit vers execve
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini = init_struct(g_mini, envp);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
		g_mini.tab = split_line(g_mini);
		exec(g_mini);
	}
	free(g_mini.line);
	free(g_mini.tab);
}
