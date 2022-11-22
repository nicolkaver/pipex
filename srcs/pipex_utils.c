/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:00:19 by nboratko          #+#    #+#             */
/*   Updated: 2022/08/10 16:34:58 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	invalid_command(char *check, char **cmd)
{
	if (!check)
	{
		if (cmd[0] && access(cmd[0], F_OK | R_OK | X_OK) != 0
			&& ft_strchr(cmd[0], '/'))
			ft_printf("bash: %s: %s\n", cmd[0], strerror(errno));
		else
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 20);
		}
	}
}

static void	write_empty(int ret)
{
	if (!ret)
		ft_putendl_fd("Command '' not found", 2);
	else
		ft_printf("bash: : No such file or directory\n");
}

static void	empty_cmd(char **argv, char **envp, int i)
{
	char	**cmd;
	char	*check;
	char	**path;
	int		ret;

	ret = 0;
	path = get_paths_unset(envp, &ret);
	if (*argv[i] == '\0')
	{
		write_empty(ret);
		if (path)
			free_split(path);
		return ;
	}
	cmd = ft_split(argv[i], ' ');
	check = get_path(cmd, envp);
	if (path)
		invalid_command(check, cmd);
	if (cmd[0] && **cmd != '/')
		free(check);
	free_split(cmd);
	if (path)
		free_split(path);
}

static void	check_loop(char **envp, char **argv, int i, int j)
{
	if (j == 0 && !envp[0])
	{	
		if (*argv[i] == '\0')
			ft_printf("env: ‘’: No such file or directory\n");
		else if (access(argv[i], X_OK) && *argv[i] == '/')
		{
			ft_printf("env: ‘%s’: %s\n", argv[i], strerror(errno));
		}
		else
			empty_cmd(argv, envp, i);
	}
	else if (j > 0 && !envp[0] && *argv[i] == '/')
	{
		if (access(argv[i], X_OK))
			ft_printf("bash: %s: %s\n", argv[i], strerror(errno));
	}
	else
	{
		empty_cmd(argv, envp, i);
	}
}

void	check_args_normal(char **argv, int argc, char **envp)
{
	int	fd;
	int	i;
	int	j;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
	if (fd != -1)
		close(fd);
	i = 1;
	if (fd == -1)
		i = 2;
	j = 0;
	while (++i < argc - 1)
	{
		if (argv[i][0] == '/' && access(argv[i], F_OK | X_OK) == 0)
			continue ;
		else
			check_loop(envp, argv, i, j);
		j++;
	}
}
