/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2022/12/13 16:17:08 by clecat           ###   ########.fr       */
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

//fonction d'interuption du programme
//affiche une nouvelle ligne ou interrompt le programme mais reste dedans
//rl_on_new_line, rl_replace_line, rl_redisplay
void	ft_interruption(int signum)
{
	(void)signum;

	printf("fonction interruption\n");
	rl_on_new_line(); //remplace la ligne actuel
	rl_redisplay();
}

//fonction de sortie du prog
void	ft_quit(int signum)
{
	(void)signum;
}

void	signaux(void)
{
	//numero_du_signal, procedure a faire
	signal(SIGINT, ft_interruption); //interruption controle c
	//signal(SIGQUIT, ft_quit);//quitte le programme controle d et '\'
}
