/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:41:04 by nboratko          #+#    #+#             */
/*   Updated: 2022/08/10 16:28:57 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

void	cmd_not_found(char **cmd, char *path, t_child *child)
{
	if (path)
		free(path);
	free_split(cmd);
	free(child->pid);
	close(child->outfile);
	close(child->pipefd[0]);
	close(child->pipefd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	child_struct_init(t_child *child, char **av, char **envp)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	child->av = av;
	child->envp = envp;
	child->n_cmd = i - 3;
	child->outfile = open(av[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (child->outfile == -1)
	{
		ft_printf("bash: %s: %s\n", av[i - 1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	child->pid = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < child->n_cmd)
		child->pid[i] = -2;
}

void	execute(char **cmd, char *path, t_child *child)
{
	execve(path, cmd, child->envp);
	write(2, "bash: ", 7);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": Permission denied", 19);
	write(2, "\n", 1);
	free_split(cmd);
	free(child->pid);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(child->pipefd[0]);
	close(child->outfile);
	exit(EXIT_FAILURE);
}

void	path_and_cmd(t_child *child, int index)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(child->av[index + 2], ' ');
	path = get_path(cmd, child->envp);
	if (cmd[0] && path)
		execute(cmd, path, child);
	else
		cmd_not_found(cmd, path, child);
}
