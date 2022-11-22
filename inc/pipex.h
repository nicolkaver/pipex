/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:54:03 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/08 12:43:58 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

/*typedef struct s_child
{
	pid_t	pid;
	int		pipefd[2];
	char	**av;
	char	**envp;
	int		n_cmd;
	int		infile;
	int		outfile;
	int		here_doc;
}			t_child;*/

int		main(int argc, char **argv, char **envp);
void	free_split(char **av);
void	cmd_not_found(char **cmd, char *path, t_child *child);
char	**get_paths(char **envp, char **cmd);
char	**get_paths_unset(char **envp, int *ret);
void	child_struct_init(t_child *child, char **av, char **envp);
char	*get_path(char **cmd, char **envp);
char	*get_path_unset(char **cmd, char **envp, int ret);
void	execute(char **cmd, char *path, t_child *child);
void	check_args_normal(char **argv, int argc, char **envp);
void	path_and_cmd(t_child *child, int index);

#endif
