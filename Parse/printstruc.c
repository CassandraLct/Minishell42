/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstruc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:01:13 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/19 16:43:40 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print what is inside the t_cmd struct
void	printstruc(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("\nlist of in-redirections\n", 1);
	while (cmd->stdin[i])
	{
		printf("[%s] -> [%s]\n", cmd->stdin[i], cmd->stdin[i + 1]);
		i += 2;
	}
	i = 0;
	ft_putstr_fd("list of out-redirections\n", 1);
	while (cmd->stdout[i])
	{
		printf("[%s] -> [%s]\n", cmd->stdout[i], cmd->stdout[i + 1]);
		i += 2;
	}
	i = 0;
	ft_putstr_fd("list of cmd and arg\n", 1);
	while (cmd->cmd[i])
	{
		printf("[%s] ", cmd->cmd[i]);
		i++;
	}
	printf("\n");
}

// print what is inside the t_cmd struct
void	printstruc2(t_cmd **cmd)
{
	int	i;

	i = 0;
	printf("\nlist of all the instructions\n");
	if (!cmd)
	{
		printf("no cmd\n");
		return ;
	}
	if (!cmd[0])
	{
		printf("no cmd[0]\n");
		return ;
	}
	if (!cmd[0]->stdin || !cmd[0]->stdout || !cmd[0]->cmd)
	{
		printf("struct empty\n");
		return ;
	}
	while (cmd[i])
	{
		printf("********** instruction[%d] **********\n", i);
		printstruc(cmd[i]);
		printf("************ pipe or end ************\n");
		i++;
	}
	printf("the end\n");
}
