/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 10:35:08 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//retour erreur ctrl c : 1 et 130 ; 131 pour ctrl-\ quit et 127 quand rien 
//fonction d'interuption du programme ctrl c
// pid = -1 is the case we are un promt, pid = 0 is child, pid > 0 is parent
void	ft_ctrl_c(int signum)
{
	if (g_mini.pid == -1)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else if (g_mini.pid > 0)
	{
		if (kill(g_mini.pid, signum) == 0)
			g_mini.ret_err = 130;
		else
			return ;
	}
	else
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit(130);
	}
	g_mini.sig_heredoc = 0;
}

//exit du ctrl-d
void	ft_ctrl_d(int signum)
{
	if (g_mini.pid == -1)
	{
		printf("exit\n");
		exit(0);
	}
	else if (g_mini.pid > 0)
	{
		if (kill(g_mini.pid, signum) == 0)
			g_mini.ret_err = 0;
		else
			return ;
	}
	else
	{
		printf("\n");
		exit(0);
	}
	g_mini.sig_heredoc = 0;
}

//ctrl\ fonction quit
void	ft_ctrl_backslash(int signum)
{
	(void)signum;
	if (g_mini.pid == -1)
	{
		printf("\e[2K");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else if (g_mini.pid > 0)
	{
	}
	else
	{
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
//	g_mini.sig_heredoc = 0;
}

//numero_du_signal, procedure a faire
void	signaux(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGTERM, ft_ctrl_d);
	signal(SIGQUIT, ft_ctrl_backslash);
}
