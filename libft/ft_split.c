/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:09 by nboratko          #+#    #+#             */
/*   Updated: 2021/12/01 18:43:25 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_wordlen(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static unsigned int	ft_wordcount(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_free(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	*ft_wordcpy(char *dest, char const *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!arr || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			arr[j] = (char *)malloc(sizeof(char) * (ft_wordlen(&s[i], c) + 1));
			if (!arr[j])
				return (ft_free(arr, j));
			ft_wordcpy(arr[j], &s[i], c);
			j++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
