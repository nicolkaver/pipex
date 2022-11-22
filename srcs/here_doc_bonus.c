/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:50:31 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/27 15:39:23 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static int	write_here_doc(t_child *child, char **tmp, int *file)
{
	int	cmp;

	write(1, "> ", 2);
	*tmp = get_next_line(STDIN_FILENO, 0);
	if (!(*tmp))
		exit(EXIT_FAILURE);
	if (ft_strlen(*tmp) - 1 == ft_strlen(child->av[2]))
		cmp = ft_strncmp(child->av[2], *tmp, ft_strlen(child->av[2] + 1));
	else
		cmp = 1;
	if (!cmp)
		return (0);
	write(*file, *tmp, ft_strlen(*tmp));
	free((*tmp));
	return (1);
}

void	get_here_doc(t_child *child)
{
	int		file;
	int		check;
	char	*tmp;

	check = 1;
	file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		ft_printf("%s\n", strerror(errno));
	while (1)
	{
		check = write_here_doc(child, &tmp, &file);
		if (check == 0)
			break ;
	}
	free(tmp);
	get_next_line(1025, 1);
	close(file);
	child->infile = open(".here_doc", O_RDONLY);
	if (child->infile == -1)
	{
		unlink(".here_doc");
		ft_perror("Error");
	}
}
