/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/07 15:03:32 by clecat           ###   ########.fr       */
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

	recup_env(envp, mini);
	while(1)
	{
		mini.line = readline("minishell>");
		add_history(mini.line);
	}
	//free(c_env);
}