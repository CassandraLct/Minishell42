/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/27 14:17:21 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
int	cotes_dollar(t_min *mini, char *line)
{
	if (verif_cotes(line) == 1)
	{
		free(mini->line);
		mini->line = ft_strdup(line);
		free(line);
		return (1);
	}
	return (0);
}

//verifie si dollar present et modifie mini.line en fonction
void	parcour_line(t_min *mini)
{
	char	*line;
	int		nb_dollar;

	nb_dollar = 0;
	verif_cmdcotes(mini->line);
	nb_dollar = count_nbdollar(mini->line);
	if (nb_dollar == 0)
		return ;
	line = ft_strdup(mini->line);
	free(mini->line);
	mini->line = rm_d_dollar(line);
	free(line);
	nb_dollar = count_nbdollar(mini->line);
	line = ft_strdup(mini->line);
	if (cotes_dollar(mini, line) == 1)
		return ;
	free(mini->line);
	mini->line = ft_strdup(line);
	free(line);
	nb_dollar = count_nbdollar(mini->line);
	if (nb_dollar > 0)
	{
		line = ft_strdup(mini->line);
		free(mini->line);
		mini->line = modif_line(line, nb_dollar);
	}
}

//renvoie vers fonction de modif line
char	*modif_line(char *line, int nb_dollar)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(line);
	tmp2 = redir_line(tmp, nb_dollar);
	free(line);
	line = ft_strdup(tmp2);
	free(tmp2);
	return (line);
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
