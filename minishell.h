/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:45 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 18:11:56 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
//# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_min
{
	char	**c_env;
	char	**c_exp;
	int		ret_err;
	char	*line;
	char	**tab;
	char	*prompt;
	char	*cdpath;
}	t_min;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
int		strdigit(char *str);
void	print_env(t_min mini);
void	export(t_min mini);
int		echo(char **arg);
char	**init_cpy(char **str, char **dest);
char	*ft_strdup(char *s);
int		tablen(t_min mini);
int		check_exp(t_min mini, int index);
void	fill_exp(t_min mini, char *str);
int		ft_isdigit(char c);
void	free_tab(char **tab);
char	**ft_cpytab(char **tab);
char	**init_exp(char **tab);
void	cd(t_min mini);
char	*ft_strjoin(char const *s1, char const *s2);
void	print_export(t_min mini);
void	exit_min(char **argv, t_min mini);
t_min	init_struct(t_min mini, char **envp);
char	**init_export(t_min mini);
void	order_exp(t_min mini);
void	unset(t_min mini);
void	exec(t_min mini, char **cmd);

#endif