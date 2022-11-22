/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_original.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:59:44 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/27 14:00:35 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_original(char *s1, char *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (s3 == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		s3[len1] = s2[i];
		len1++;
	}
	s3[len1] = '\0';
	return (s3);
}
