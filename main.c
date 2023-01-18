/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/18 22:19:54 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// grep >test < Makefile "minishell" | cat test
// commencer le lexer split la line et puis checker premier arg si c'est une 
// commande

t_min	g_mini;

//probleme a regler: valeur modifier non remonter, probleme avec l'historique
//modifier le split de la line
int	main(int argc, char **argv, char **envp)
{
	char	**tstspl;
	t_cmd	**instruc;
	
	tstspl = NULL;
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
	//	g_mini.tab = split_line(g_mini);
		
		tstspl = spliter();
		instruc = spliter3(tstspl);
		printstruc2(instruc);

	//	redirection(&g_mini);
	//	signaux();
		free(g_mini.line);
	//	free_tab(g_mini.tab);
	}
	free_all(g_mini);
}
