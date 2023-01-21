/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/20 18:15:57 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test
//modifier le split de la line
int	main(int argc, char **argv, char **envp)
{
	char	**tstspl;
//	t_cmd	**instruc;
	
	tstspl = NULL;
	(void)argc;
	(void)argv;
	init_struct(&g_mini, envp);
	//signaux();
	while (1)
	{
		g_mini.line = readline(g_mini.prompt);
		if (g_mini.line == NULL)
			signal_exit();
		add_history(g_mini.line);
		parcour_line(&g_mini);
		if(g_mini.line != NULL)
		{
			// g_mini.tab = ft_split(g_mini.line, 32);
			g_mini.struct_cmd = spliter3(spliter());
			redir_pipe(&g_mini, g_mini.struct_cmd);
			// printf("ici 1\n");
			free(g_mini.line);
			// printf("ici 2\n");
			// // free_tab(g_mini.tab);
			// printf("ici 3\n");
		}
		free_t_cmd();
	}
	free_all(g_mini);
}
