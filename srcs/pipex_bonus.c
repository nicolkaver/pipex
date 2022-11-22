/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:44:11 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/01 13:56:56 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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
			ft_printf("bash: %s %s\n", strerror(errno));
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
		ft_printf("bash: %s %s\n", strerror(errno));
	if (child->pid[i] == 0)
		pipex_loop2(child, i);
}

static void	pipex(t_child *child)
{
	int	i;
	int	status;

	i = -1;
	if (!child->here_doc)
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

	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1] + 1)))
			child.here_doc = 0;
		else if (ft_strlen(argv[1]) != ft_strlen("here_doc"))
			child.here_doc = 0;
		else
			child.here_doc = 1;
	}
	else
		child.here_doc = 0;
	if (!child.here_doc)
		check_args_normal_bonus(argv, argc, envp);
	if (child.here_doc)
		check_args_here_doc(argv, argc);
	child_struct_init(&child, argv, envp);
	pipex(&child);
	if (child.here_doc)
		unlink(".here_doc");
	close(child.outfile);
	free(child.pid);
	return (0);
}
