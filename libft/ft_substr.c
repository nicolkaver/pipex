/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:00:25 by nboratko          #+#    #+#             */
/*   Updated: 2021/12/01 17:43:48 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_len(char const *s, unsigned int start, size_t len)
{
	unsigned int	l;

	l = 0;
	if ((start + len) <= ft_strlen(s))
		l = len;
	if ((start + len) > ft_strlen(s))
	{
		while (s[start + l])
			l++;
	}
	return (l);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	l = ft_get_len(s, start, len);
	s2 = (char *)malloc(sizeof(char) * (l + 1));
	if (!s2)
		return (NULL);
	while (i < l && s[start + i])
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
