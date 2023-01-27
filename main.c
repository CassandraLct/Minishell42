/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:38 by clecat            #+#    #+#             */
/*   Updated: 2023/01/27 15:51:10 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//grep >test < Makefile "minishell" | cat test

// int	heredoc(t_cmd **cmd)
// {
// 	char	*line;
// 	int		pp[2];
	
// 	pipe(pp);
// 	if (cmd[0]->stdin[0] == NULL)
// 		return (1);
// 	if (cmd[0]->stdin[0] != NULL && cmd[0]->stdin[1] == NULL) // segfault
// 	{
// 		printf("minishell: syntax error near unexpected token `newline'\n");
// 		g_mini.ret_err = 258;
// 		return (1);
// 	}
// 	else
// 	{
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if(ft_strncmp(cmd[0]->stdin[1], line, ft_strlen(line)) == 0)
// 			{
// 				free(line);
// 				close(pp[1]);
// 				return(pp[0]);
// 			}
// 			write(pp[1], line, ft_strlen(line));
// 			write(pp[1], "\n", 1);
// 			free(line);
// 		}
// 	}
// }

//modifier le split de la line // test a faire : ec'ho | cat ex'ec.c
int	main(int argc, char **argv, char **envp)
{
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
	free_all(g_mini);
}
