/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/21 19:42:04 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//modifier le split de la line
int	main(int argc, char **argv, char **envp)
{
	char	**tstspl;

	tstspl = NULL;
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
		parcour_line(&g_mini);
		if (g_mini.line != NULL)
		{
			g_mini.struct_cmd = spliter3(spliter());
			printf("main avant freeline, g_line = %s\n", g_mini.line);
			free(g_mini.line);
			printf("main apres freeline\n");
			redir_pipe(&g_mini, g_mini.struct_cmd);
			free_t_cmd(g_mini.struct_cmd);
		}
	}
	free_all(g_mini);
}
