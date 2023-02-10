/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 16:47:46 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//retour erreur ctrl c : 1 et 130 ; 131 pour ctrl-\ quit et 127 quand rien 
//fonction d'interuption du programme ctrl c
// pid = -1 is the case we are un promt, pid = 0 is child, pid > 0 is parent

//used for showing ^C or not
void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

//fonctionne dans le heredoc et en dehors (enfants et parent affiche le prompt)
void	ft_signal(int signum)
{
	(void)signum;
	g_mini.sig_heredoc = 0;
	if (g_mini.pid == 0)
	{
		write(1, "\n", 1);
		close(0);
	}
	else
	{
		printf("\n");
		if (g_mini.rl_done == 1)
			return ;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_mini.ret_err = 1;
}

//ajouter le comportement du heredoc
void	ft_signalquit(int signum)
{
	(void)signum;
	g_mini.sig_heredoc = 0;
	if (g_mini.pid != 0)
	{
		printf("Quit: 3\n");
		g_mini.ret_err = 131;
		return ;
	}
	rl_on_new_line();
	rl_redisplay();
}

//exit du ctrl-d
void	signal_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	signaux2(void)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signalquit);
	echo_control_seq(g_mini.in_cmd);
}
