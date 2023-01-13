/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/13 14:58:39 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//modifier le split de la line
int	main(int argc, char **argv, char **envp)
{
	int	i;
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	signaux();
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		if (g_mini.line == NULL)
			signal_exit();
		add_history(g_mini.line);
		//g_mini.tab = split_line(g_mini);
		g_mini.tab = split_onpipe(g_mini);
		i = 0;
		while (g_mini.tab[i])
			printf("%s\n", g_mini.tab[i++]);
		// redirection(&g_mini);
		// free(g_mini.line);
		// free_tab(g_mini.tab);
	}
	free_all(g_mini);
}
