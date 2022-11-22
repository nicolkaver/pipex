/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:49:36 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/27 15:42:14 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

char	*get_raw_line(int fd, char *tmp, int a)
{
	char	*buf;
	ssize_t	nbytes;

	if (a)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	nbytes = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr(tmp, '\n') && nbytes != 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(buf), NULL);
		buf[nbytes] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	free(buf);
	return (tmp);
}

char	*get_final_line(char *tmp)
{
	char	*str;
	int		i;

	i = 0;
	if (!tmp[i])
		return (free(tmp), NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (free(tmp), NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	if (tmp[i] && tmp[i] == '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_rest(char *tmp)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
		return (free(tmp), NULL);
	len = ft_strlen(tmp);
	str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!str)
		return (free(tmp), NULL);
	i++;
	while (tmp[i])
		str[j++] = tmp[i++];
	str[j] = '\0';
	free(tmp);
	return (str);
}

char	*get_next_line(int fd, int a)
{
	char		*ret;
	static char	*tmp;

	if (fd == 1025)
		return (free(tmp), NULL);
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (a)
		tmp = get_raw_line(fd, tmp, 1);
	if (!a)
		tmp = get_raw_line(fd, tmp, 0);
	if (tmp == NULL)
	{
		free(tmp);
		return (NULL);
	}
	ret = get_final_line(tmp);
	tmp = get_rest(tmp);
	return (ret);
}
