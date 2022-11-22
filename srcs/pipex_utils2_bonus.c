/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:41:04 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/07 20:29:47 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	free_split(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

static void	malloc_pid(t_child *child)
{
	int	i;

	i = -1;
	child->pid = malloc(sizeof(pid_t) * child->n_cmd);
	while (++i < child->n_cmd)
		child->pid[i] = -2;
}

void	child_struct_init(t_child *child, char **av, char **envp)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	child->av = av;
	child->envp = envp;
	if (!child->here_doc)
	{
		child->n_cmd = i - 3;
		child->outfile = open(av[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (child->here_doc)
	{	
		child->n_cmd = 2;
		get_here_doc(child);
		child->outfile = open(av[i - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	if (child->outfile == -1)
	{
		ft_printf("bash: %s: %s\n", av[i - 1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	malloc_pid(child);
}

void	execute(char **cmd, char *path, t_child *child)
{
	execve(path, cmd, child->envp);
	write(2, "bash: ", 7);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": Permission denied", 19);
	write(2, "\n", 1);
	free(child->pid);
	free_split(cmd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(child->pipefd[0]);
	exit(EXIT_FAILURE);
}

void	path_and_cmd(t_child *child, int index)
{
	char	**cmd;
	char	*path;

	if (!child->here_doc)
		cmd = ft_split(child->av[index + 2], ' ');
	if (child->here_doc)
		cmd = ft_split(child->av[index + 3], ' ');
	path = find_path(cmd, child->envp);
	if (cmd[0] && path)
		execute(cmd, path, child);
	else
		cmd_not_found(cmd, path, child);
}
