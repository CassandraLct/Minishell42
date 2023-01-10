/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/10 17:48:35 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// bash-3.2$ cat | ls
// Built-in        exec.o
// Comments+Docs   libreadline.a
// Makefile        main.c
// Parse           main.o
// ResteaFaire.txt minishell
// Utils           minishell.h
// exec.c
// ^C (avec ctrl-c)
// bash-3.2$ cat | ls
// Built-in        ResteaFaire.txt libreadline.a   minishell.h
// Comments+Docs   Utils           main.c
// Makefile        exec.c          main.o
// Parse           exec.o          minishell
// ^\bash-3.2$ (aver ctrl-\)
// bash-3.2$ cat | ls
// Built-in        ResteaFaire.txt libreadline.a   minishell.h
// Comments+Docs   Utils           main.c
// Makefile        exec.c          main.o
// Parse           exec.o          minishell
// bash-3.2$ (avec ctrl-D)
// bash-3.2$ grep -v MAkefile
// ^C
// bash-3.2$ grep -v MAkefile
// ^\Quit: 3
// bash-3.2$ grep -v MAkefile
// bash-3.2$ grep -v MAkefile
// ^D
/* signaux: ctrl-c / ctrl-d / ctrl-\
fonction potentiellement utile :signal, sigaction, sigemptyset, sigaddset,
kill*/
//fonction d'intteruption du programme ctrl c
//interrompt le programme mais reste dedans signum = 2
void	ft_interruption(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//fonction de sortie du prog ctrl d et '\'
//controle d fonctionne la premiere fois mais seg fault la deuxieme fois (d'affiler)
//controle \ quite directement
void	ft_quit(int signum)
{
	(void)signum;
	// if(signum == SIGQUIT)
	// 	printf("^\\Quit:3\n");
	printf("\e[2K");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//numero_du_signal, procedure a faire
void	signaux(void)
{
	signal(SIGINT, ft_interruption);
	signal(SIGQUIT, ft_quit);
}

// voir fonction signal, sigaction, sigemptyset, sigaddset, kill
// si cmd boucle et fait controle \ affiche ^\Quit:3
