/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/22 13:27:02 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et 

t_min	g_mini;

//probleme a regler: valeur modifier non remonter
//finir export, faire la base d'excve,modifier le split la line
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini = init_struct(g_mini, envp);
	export(g_mini);
	//exec(g_mini, argv[1]);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
	}
}
