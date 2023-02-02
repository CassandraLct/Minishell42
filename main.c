/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/02 13:41:14 by clecat           ###   ########.fr       */
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
//		dprintf(2, "in main 1, line=[%s]\n", g_mini.line);
		if (g_mini.line == NULL)
		{
			dprintf(2, "signal ");
			signal_exit();
		}
//		dprintf(2, "in main 2, line=[%s]\n", g_mini.line);
		add_history(g_mini.line);
//		dprintf(2, "in main 3, line=[%s]\n", g_mini.line);
		parcour_line(&g_mini);
//		dprintf(2, "in main 4, line=[%s]\n", g_mini.line);
		g_mini.line = verif_cmdcotes(g_mini.line);
//		dprintf(2, "in main 5, line=[%s]\n", g_mini.line);
		printf("////////////TEST1///////////////////\n");
		system("leaks minishell");
		if (g_mini.line[0] != '\0')
		{
			// printf("avant split line\n");
//			dprintf(2, "in main 6, line=[%s]\n", g_mini.line);
			printf("////////////TEST2///////////////////\n");
			system("leaks minishell");
			g_mini.struct_cmd = spliter3(spliter());
			printf("////////////TEST3///////////////////\n");
			system("leaks minishell");
//			printstruc2(g_mini.struct_cmd);
			// printf("apres split_line\n");
			if (g_mini.struct_cmd != NULL)
			{
//				dprintf(2, "in maim loop 1\n");
				verif_struct_cmd(g_mini.struct_cmd);
				printf("////////////TEST4///////////////////\n");
				system("leaks minishell");
//				dprintf(2, "in maim loop 2\n");
				redir_pipe(&g_mini, g_mini.struct_cmd);
				printf("////////////TEST5///////////////////\n");
				system("leaks minishell");
//				dprintf(2, "in maim loop 3\n");
				free_t_cmd(g_mini.struct_cmd);
				printf("////////////TEST6///////////////////\n");
				system("leaks minishell");
//				dprintf(2, "in maim loop 4\n");
			}
		}
// double free ici je suis dessus RDM
		free(g_mini.line);
		printf("////////////END MAIN///////////////////\n");
		system("leaks minishell");
		// printf("apres le free line\n");
	}
//	dprintf(2, "in main end 4\n");
	free_all(g_mini);
}
