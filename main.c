/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 17:00:00 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//commencer le lexer split la line et 

t_min	g_mini;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini.prompt = "minishell>";
	g_mini.c_env = recup_env(envp, g_mini);
	export(g_mini);
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		add_history(g_mini.line);
	}
}
