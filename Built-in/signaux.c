/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2022/12/19 16:51:08 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* signaux: ctrl-c / ctrl-d / ctrl-\
fonction potentiellement utile :signal, sigaction, sigemptyset, sigaddset, kill, exit
quand prog en train de compiler
ctrl-D kill le term
ctrl-C stop le prog et affiche err
ctrl-\ stop le prog
ctrl-c dans heredoc quitte heredoc
ctrl-d dans heredoc affiche erreur grep puis quitte
ctrl-\ dans heredoc ne fait rien*/
//fonction d'intteruption du programme ctrl c
//affiche une nouvelle ligne ou interrompt le programme mais reste dedans
//rl_on_new_line, rl_replace_line, rl_redisplay
void	ft_interruption(int signum)
{
	(void)signum;
	//printf("fonction interruption\n");
	rl_on_new_line(); //remplace la ligne actuel
	//rl_replace_line("", 0); non detecter par le makefile
	rl_redisplay();
}

//fonction de sortie du prog ctrl d et '\'
void	ft_quit(int signum)
{
	(void)signum;
}

//numero_du_signal, procedure a faire
void	signaux(void)
{
	signal(SIGINT, ft_interruption);
	//signal(SIGQUIT, ft_quit);
}
