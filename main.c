/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/29 17:28:53 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_min	g_mini;

//modifier le split de la line // test a faire : ec'ho | cat ex'ec.c
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	signaux();
	while (1)
	{
//		dprintf(2, "in main, in loop 1\n");
		g_mini.line = readline(g_mini.prompt);
//		dprintf(2, "in main, in loop 2\n");
		if (g_mini.line == NULL)
			signal_exit();
//		dprintf(2, "in main, in loop 3\n");
		add_history(g_mini.line);
		parcour_line(&g_mini);
		printf("line main1 = {%s}\n", g_mini.line);
		verif_cmdcotes(g_mini.line);
		printf("linemain = {%s}\n", g_mini.line);
		if (g_mini.line[0] != '\0')
		{
			g_mini.struct_cmd = spliter3(spliter());
			if (g_mini.struct_cmd != NULL)
			{
				verif_struct_cmd(g_mini.struct_cmd);
				redir_pipe(&g_mini, g_mini.struct_cmd);
				free_t_cmd(g_mini.struct_cmd);
			}
		}
		free(g_mini.line);
	}
//	dprintf(2, "in main end 4\n");
	free_all(g_mini);
}
