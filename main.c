/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/18 18:09:31 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et 

t_min	g_mini;

//probleme a regler: la modifification de c_env n'est pas remonter
//samedi: faire cd, raccourcir pwd, modifier check_exp, faire un init_structure
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini.ret_err = 0;
	g_mini.prompt = "minishell>";
	g_mini.c_env = ft_cptab(envp);
	g_mini.cdpath = ".";
	cd(g_mini);
	/*print_env(g_mini);
	printf("  --------------  \n");*/
	export(g_mini);
	//print_env(g_mini);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
	}
}
