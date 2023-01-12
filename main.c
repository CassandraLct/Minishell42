/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/12 11:17:17 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// grep >test < Makefile "minishell" | cat test
// commencer le lexer split la line et puis checker premier arg si c'est une 
// commande



//probleme a regler: valeur modifier non remonter, probleme avec l'historique
//modifier le split de la line
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	signaux();
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		if(g_mini.line == NULL)
			signal_exit();
		add_history(g_mini.line);
		g_mini.tab = split_line(g_mini);
		redirection(&g_mini);
		free(g_mini.line);
		free_tab(g_mini.tab);
	}
	free_all(g_mini);
}
