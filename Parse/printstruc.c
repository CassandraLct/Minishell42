
#include "minishell.h"

// print what is inside the t_cmd struct
void	printstruc(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("\nlist of in-redirections\n", 1);
	while (cmd->stdin[i])
	{
		write(1, "[", 1);
		ft_putstr_fd(cmd->stdin[i], 1);
		write(1, "] -> [", 6);
		ft_putstr_fd(cmd->stdin[i + 1], 1);
		write(1, "]\n", 2);
		i += 2;
	}
	i = 0;
	ft_putstr_fd("list of out-redirections\n", 1);
	while (cmd->stdout[i])
	{
		write(1, "[", 1);
		ft_putstr_fd(cmd->stdout[i], 1);
		write(1, "] -> [", 6);
		ft_putstr_fd(cmd->stdout[i + 1], 1);
		write(1, "]\n", 2);
		i += 2;
	}
	i = 0;
	ft_putstr_fd("list of cmd and arg\n", 1);
	while (cmd->cmd[i])
	{
		write(1, "[", 1);
		ft_putstr_fd(cmd->cmd[i], 1);
		write(1, "] ", 3);
		i++;
	}
	write(1, "\n", 1);
}

// print what is inside the t_cmd struct
void	printstruc2(t_cmd **cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("\nlist of all the instructions\n", 1);
	while (cmd[i])
	{
		printf("********** instruction[%d] **********\n", i);
		printstruc(cmd[i]);
		printf("************ pipe or end ************\n");
		i++;
	}
	ft_putstr_fd("the end\n", 1);
}
