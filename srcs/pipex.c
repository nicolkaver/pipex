/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:44:11 by nboratko          #+#    #+#             */
/*   Updated: 2022/08/10 16:35:07 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(t_child *child, int index)
{
	close(child->pipefd[0]);
	if (index == child->n_cmd - 1)
	{
		if (dup2(child->outfile, STDOUT_FILENO) == -1)
			ft_printf("bash: %s\n", strerror(errno));
		close(child->outfile);
	}
	else if (index == 0)
	{
		if (child->infile != -1)
		{
			if (dup2(child->pipefd[1], STDOUT_FILENO) == -1)
				ft_printf("bash: %s\n", strerror(errno));
		}
	}
	else
	{
		if (dup2(child->pipefd[1], STDOUT_FILENO) == -1)
			ft_printf("bash: %s\n", strerror(errno));
	}
	close(child->pipefd[1]);
	path_and_cmd(child, index);
}

static void	pipex_loop2(t_child *child, int i)
{
	close(child->pipefd[0]);
	if (i == 0)
	{
		if (child->infile != -1)
			child_process(child, i);
	}
	if (i > 0)
		child_process(child, i);
}

static void	pipex_loop(t_child *child, int i)
{
	if (i > 0)
	{
		if (dup2(child->pipefd[0], STDIN_FILENO) == -1)
			ft_printf("bash: %s\n", strerror(errno));
		close(child->pipefd[0]);
	}
	if (pipe(child->pipefd) == -1)
		ft_printf("bash: %s\n", strerror(errno));
	if (i == 0)
	{
		if (child->infile != -1)
			child->pid[i] = fork();
	}
	if (i > 0)
		child->pid[i] = fork();
	if (child->pid[i] == -1)
		ft_printf("bash: %s\n", strerror(errno));
	if (child->pid[i] == 0)
		pipex_loop2(child, i);
}

static void	pipex(t_child *child)
{
	int	i;
	int	status;

	i = -1;
	child->infile = open(child->av[1], O_RDONLY);
	if (child->infile != -1)
	{
		if (dup2(child->infile, STDIN_FILENO) == -1)
			ft_printf("bash: %s\n", strerror(errno));
		close(child->infile);
	}
	while (++i < child->n_cmd)
	{
		pipex_loop(child, i);
		close(STDIN_FILENO);
		close(child->pipefd[1]);
	}
	i = -1;
	while (++i < child->n_cmd)
		waitpid(child->pid[i], &status, 0);
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (child->infile != -1)
		close(child->infile);
}

int	main(int argc, char **argv, char **envp)
{
	t_child	child;

	if (argc != 5)
	{
		ft_putendl_fd("Format: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	check_args_normal(argv, argc, envp);
	child_struct_init(&child, argv, envp);
	pipex(&child);
	close(child.outfile);
	free(child.pid);
	return (0);
}
