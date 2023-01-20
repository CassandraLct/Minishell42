/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:43:29 by clecat            #+#    #+#             */
/*   Updated: 2023/01/20 16:55:45 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//5 fonctions

//change le $? par le dernier retour_erreur enregistrer
// void	dollar_reterr(char *line)
// {
// 	char	*tmp;
// 	char	*start;
// 	char	*end;
// 	int		i;

// 	start = recup_startline(line);
// 	i = ft_strlen(start) + 1;
// 	tmp = ft_strjoin(start, ft_itoa(g_mini.ret_err));
// 	free(start);
// 	while (line[i] && line[i] != ' ' && line[i] != '\0')
// 		i++;
// 	if (i == ft_strlen(line))
// 	{
// 		free(line);
// 		line = ft_strdup(tmp);
// 		free(tmp);
// 	}
// 	else
// 	{
// 		end = recup_endline(i, g_mini.line);
// 		free(line);
// 		line = ft_strjoin(tmp, end);
// 		free(tmp);
// 		free(end);
// 	}
// }

// //gestion dollar /segfault lors de cd$bonjour$$$HOME
// void	ft_dollar(char *str)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (str[i] == '?')
// 		dollar_reterr(g_mini.line);
// 	tmp = ft_strjoin(str, "=");
// 	while (g_mini.c_env[i])
// 	{
// 		if (ft_strncmp(g_mini.c_env[i], tmp, ft_strlen(tmp)) == 0)
// 			break ;
// 		i++;
// 	}
// 	free(tmp);
// 	if (i == tablen(g_mini.c_env))
// 	{
// 		rm_dollarvar(g_mini.line, str);
// 		if (!g_mini.line)
// 			return ;
// 	}
// 	else
// 	{
// 		tmp = recup_valvar(g_mini.c_env[i]);
// 		change_linevar(tmp, g_mini.line);
// 		free(tmp);
// 	}
// }
