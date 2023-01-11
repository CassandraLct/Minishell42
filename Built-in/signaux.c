/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/11 16:42:43 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//fonction d'intteruption du programme ctrl c
void	ft_interruption(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//ctrlD ou ctrl\ fonction quit
void	ft_quit(int signum)
{
	if(g_mini.pid != 0)
	{
		if (!kill(g_mini.pid, signum))
			printf("Quit: 3\n");
	}
	else
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//numero_du_signal, procedure a faire
void	signaux()
{
	signal(SIGINT, ft_interruption);
	signal(SIGQUIT, ft_quit);
}
