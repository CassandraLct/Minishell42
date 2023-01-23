/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/23 14:02:02 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions

//faire une copie de la line avant ?/ +25 lignes
void	parcour_line(t_min *mini)
{
	char	*tmp;
	char	*line;
	int		nb_dollar;

	nb_dollar = 0;
	line = malloc(sizeof(char) * (ft_strlen(mini->line) + 1));
	tmp = NULL;
	line = ft_strdup(mini->line);
	nb_dollar = count_nbdollar(line);
	if (nb_dollar == 0)
		return ;
	free(mini->line);
	mini->line = rm_d_dollar(line);
	//free(tmp);
	nb_dollar = count_nbdollar(mini->line);
	if (nb_dollar > 0)
	{
		tmp = ft_strdup(mini->line);
		free(mini->line);
		mini->line = redir_line(tmp, nb_dollar);
	}
	return ;
}

//faire fonction de redir cmd simple ou multiple
void	redir_pipe(t_min *mini, t_cmd **cmd)
{
	if (cmd[1] == NULL)
		redirection(mini, cmd);
	else
		printf("gestion_pipe\n");
}

//built-in : cd/echo/env/exit/export/unset
//redirige soit vers les built-in soit vers execve
void	redirection(t_min *mini, t_cmd **cmd)
{
	if (cmd[0]->cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd[0]->cmd[0], "exit") == 0)
		exit_min(mini, cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "echo") == 0)
		echo(cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "env") == 0)
		ft_env(mini, cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "cd") == 0)
		cd(mini, cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "export") == 0)
		export(mini, cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "unset") == 0)
		unset(mini, cmd[0]->cmd);
	else if (ft_strcmp(cmd[0]->cmd[0], "pwd") == 0)
		pwd(mini->c_env, cmd[0]->cmd);
	else
		ft_set_pathexec(mini, cmd[0]->cmd);
}
