/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:08:29 by kevyn             #+#    #+#             */
/*   Updated: 2022/12/20 14:55:54 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//exemples de signaux
// #include "../includes/minishell.h"

//fonctions signaux minishell Thomas
/*void	interrupt_signal(int signal)
{
	(void) signal;
	if (g_stock.fork)
	{
		kill(g_stock.fork, SIGINT);
		write(1, "\n", 1);
		g_stock.fork = 0;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_signal(int signum)
{
	if (g_stock.fork)
	{
		kill(g_stock.fork, signum);
		if (signum == SIGQUIT)
			printf("^\\Quit: 3\n");
		g_stock.fork = 0;
		return ;
	}
	if (signum == 11)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int is_printed)
{
	struct termios	t;

	tcgetattr(0, &t);
	if (is_printed)
		(&t)->c_lflag |= ECHOCTL;
	else
		(&t)->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}*/

/*_____________________________________________________________*/

//fonctions signaux minishell Marie
/*void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

void	ft_signal(int signum)
{
	(void)signum;
	if (g_global.here == 1)
	{
		printf("\r");
		write(1, "\n", 1);
		close(0);
	}
	else
	{
		printf("\r");
		printf("\n");
		if (rl_done)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_global.status = 1;
}

void	ft_signalquit(int signum)
{
	(void)signum;
	if (rl_done)
	{
		printf("Quit: 3\n");
		g_global.status = 131;
		return ;
	}
	printf("\e[2K");
	rl_on_new_line();
	rl_redisplay();
	g_global.status = 0;
}

void	signal_exit(void)
{
	printf("\033[1A");
	printf("%s", rl_prompt);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	init_signals(void)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signalquit);
	echo_control_seq(0);
}*/
