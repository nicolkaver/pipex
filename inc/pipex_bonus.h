/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:54:03 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/07 16:02:30 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
char	*find_path(char **cmd, char **envp);
void	child_struct_init(t_child *child, char **av, char **envp);
void	execute(char **cmd, char *path, t_child *child);
void	get_here_doc(t_child *child);
void	check_args_normal_bonus(char **argv, int argc, char **envp);
void	check_args_here_doc(char **argv, int argc);
void	path_and_cmd(t_child *child, int index);

//GET_NEXT_LINE

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_raw_line(int fd, char *tmp, int a);
char	*get_final_line(char *tmp);
char	*get_rest(char *tmp);
char	*get_next_line(int fd, int a);

#endif
