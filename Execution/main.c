/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 13:05:20 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_min	g_mini;

// inside the while in the main
void	inside_main(void)
{
	verif_struct_cmd(g_mini.struct_cmd);
	redir_pipe(&g_mini, g_mini.struct_cmd);
}

// before the while in the main 
void	step1_main(void)
{
	add_history(g_mini.line);
	parcour_line(&g_mini);
	verif_cmdcotes(&g_mini);
	g_mini.line = verif_pipes(g_mini.line);
}

//exit du ctrl-d
void	signal_exit(void)
{
	printf("exit\n");
	exit(0);
}

//modifier le split de la line // test a faire : ec'ho | cat ex'ec.c
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	while (1)
	{
		signaux();
		g_mini.pid = -1;
		g_mini.sig_heredoc = 1;
		g_mini.line = readline(g_mini.prompt);
		if (g_mini.line == NULL)
			signal_exit();
		step1_main();
		if (g_mini.line[0] != '\0')
		{
			g_mini.struct_cmd = spliter3(spliter());
			if (g_mini.struct_cmd != NULL)
			{
				inside_main();
				free_t_cmd(g_mini.struct_cmd);
			}
		}
		free(g_mini.line);
	}
	free_all(g_mini);
}
