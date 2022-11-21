/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 14:46:48 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et 

t_min	g_mini;

//probleme a regler: la modifification de c_env n'est pas remonter quand var ajouter
//samedi: finir cd & export
//voir si les valeurs modifier remonte
//init c_exp des le depart 
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini = init_struct(g_mini, envp);
	export(g_mini);
	//print_export(g_mini);
	//print_env(g_mini);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
	}
}
