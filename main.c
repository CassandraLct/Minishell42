/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/12/13 16:15:58 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// grep >test < Makefile "minishell" | cat test
// commencer le lexer split la line et puis checker premier arg si c'est une 
// commande

t_min	g_mini;

//test en gerant la ligne sans split
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

//probleme a regler: valeur modifier non remonter, probleme avec l'historique
//modifier le split de la line
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
		g_mini = redirection(g_mini);
		signaux();
		free(g_mini.line);
		free_tab(g_mini.tab);
	}
	free_all(g_mini);
}
