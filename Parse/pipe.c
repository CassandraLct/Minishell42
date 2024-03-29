/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/13 18:13:21 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//4 fonctions
//test chaque path puis execute la cmd si existante
void	ft_exec2(t_min *mini, char **all_path, char **pathcmd, char **cmd)
{
	if (verif_cmd(all_path, pathcmd, cmd) != 0)
	{
		free_tab(all_path);
		free_tab(pathcmd);
		exit(g_mini.ret_err);
	}
	else
	{
		ft_execve(mini, all_path, pathcmd, cmd);
		free_tab(all_path);
		free_tab(pathcmd);
	}
}

void	ft_set_pathexec2(t_min *mini, char **cmd)
{
	char	**all_path;
	char	**pathcmd;

	pathcmd = NULL;
	pathcmd = init_cmd(cmd, pathcmd);
	all_path = recup_path(mini);
	if (all_path == NULL || cmd[0][0] == '/')
	{
		mini->ret_err = 127;
		ft_print_error_msg3("minishell: ", cmd[0],
			": No such file or directory\n");
		free_tab(pathcmd);
		return ;
	}
	ft_exec2(mini, all_path, pathcmd, cmd);
}

int	**ft_create_pipe(t_cmd **cmd)
{
	int	nbcmd;
	int	**pp;
	int	i;

	nbcmd = 0;
	while (cmd[nbcmd])
		nbcmd++;
	pp = ft_test(ft_calloc(nbcmd + 1, sizeof(*pp)), NULL);
	i = 0;
	while (i < nbcmd)
	{
		pp[i] = ft_test(ft_calloc(2, sizeof(**pp)), NULL);
		i++;
	}
	return (pp);
}

//main function to manage pipes
int	piping(void)
{
	int		i;
	pid_t	pid;
	int		**pp;

	echo_control_seq(1);
	pp = ft_create_pipe(g_mini.struct_cmd);
	i = 0;
	while (g_mini.struct_cmd[i + 1])
	{
		if (pipe(pp[i]) == -1)
			perror("pipe: ");
		pid = fork();
		g_mini.pid = pid;
		if (pid == -1)
			exit (127);
		if (pid == 0)
			ft_child(g_mini.struct_cmd, pp, i);
		else
			ft_parent(pp, i);
		i++;
	}
	ft_last_command(g_mini.struct_cmd, pp, i);
	ft_wait_all();
	free_tab((char **)pp);
	echo_control_seq(0);
	return (1);
}
