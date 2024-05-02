/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_assing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:36:31 by ael-maim          #+#    #+#             */
/*   Updated: 2024/03/28 23:16:56 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_assign(char *cmd, char **envp, t_pipe *ps)
{
	ps->cmd = ft_get_cmd(cmd);
	ps->path = ft_get_path(envp, ps->cmd);
	ps->arg = ft_split(cmd, ' ');
	if (!ps->path)
	{
		ft_print_error(ps->cmd);
		ft_exit(ps, 127);
	}
}

t_pipe	*ft_init_ps(int ac, char **av, t_pipe *ps)
{
	ps = malloc(sizeof(t_pipe));
	if (!ps)
		exit(1);
	ps->path = NULL;
	ps->cmd = NULL;
	ps->arg = NULL;
	ps->limiter = NULL;
	ps->file1 = av[1];
	ps->file2 = av[ac - 1];
	ps->av = av;
	ps->ac = ac;
	ps->save_stdin = dup(STDIN_FILENO);
	if (ps->save_stdin == -1)
		ft_exit(ps, 1);
	return (ps);
}

int	ft_wexitstatus(int status)
{
	status = status >> 8;
	status = status & 255;
	return (status);
}
