/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/09 21:53:11 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_min	g_mini;

void	inside_main(void)
{
	verif_struct_cmd(g_mini.struct_cmd);
	redir_pipe(&g_mini, g_mini.struct_cmd);
	free_t_cmd(g_mini.struct_cmd);
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
		add_history(g_mini.line);
		parcour_line(&g_mini);
		g_mini.line = verif_cmdcotes(g_mini.line);
		g_mini.line = verif_pipes(g_mini.line);
		if (g_mini.line[0] != '\0')
		{
			g_mini.struct_cmd = spliter3(spliter());
			if (g_mini.struct_cmd != NULL)
				inside_main();
		}
		free(g_mini.line);
	}
	free_all(g_mini);
}
