/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/12 11:47:47 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//retour erreur ctrl c : 1 et 130 ; 131 pour ctrl-\ quit et 127 quand rien 
//fonction d'interuption du programme ctrl c
void	ft_interruption(int signum)
{
	if (g_mini.pid != 0)
	{
		if (!kill(g_mini.pid, signum))
		{
			printf("\n");
			g_mini.ret_err = 130;
		}
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini.ret_err = 1;
	}
}

//ctrl\ fonction quit
void	ft_quit(int signum)
{
	if (g_mini.pid != 0)
	{
		if (!kill(g_mini.pid, signum))
		{
			printf("Quit: 3\n");
			g_mini.ret_err = 131;
		}
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//exit du ctrl-d
void	signal_exit(void)
{
	printf("exit\n");
	exit(0);
}

//numero_du_signal, procedure a faire
void	signaux(void)
{
	signal(SIGINT, ft_interruption);
	signal(SIGQUIT, ft_quit);
}
