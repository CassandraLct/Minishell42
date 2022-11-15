/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/14 12:40:04 by clecat           ###   ########.fr       */
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

	mini.prompt = "minishell>";
	recup_env(envp, mini);
	while(1)
	{
		mini.line = readline(mini.prompt);
		add_history(mini.line);
	}
	//free(c_env);
}