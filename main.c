/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/15 16:10:22 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et 

g_min mini;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//char **arg; checker echo

	//arg = malloc(sizeof(char *) * 4);
	//arg[0] = "echo";
	/*arg[1] = "-nnnnnnnn";
	arg[2] = "Bonjour";
	arg[3] = "42";*/
	//arg[1] = NULL;
	mini.prompt = "minishell>";
	//echo(arg);
	mini.c_env= recup_env(envp, mini);
	export(mini);
	//print_env(mini);
	while(1)
	{
		mini.line = readline(mini.prompt);
		add_history(mini.line);
	}
	//free(c_env);
}