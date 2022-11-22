/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:08:09 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/07 20:33:03 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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

void	check_args_here_doc(char **argv, int argc)
{
	if (argc != 6)
	{
		ft_putendl_fd("Invalid number of arguments for option here_doc", 2);
		exit(EXIT_FAILURE);
	}
	while (argc > 4)
	{
		if (*argv[argc - 2] == '\0')
		{
			ft_putendl_fd("Command '' not found", 2);
		}
		argc--;
	}
}
