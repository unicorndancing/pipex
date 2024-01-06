/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:43:18 by elraira-          #+#    #+#             */
/*   Updated: 2023/12/07 16:28:18 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_get(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_get(char *s, int c)
{
	int	i;

	i = 0;
	c = (char) c;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen_get(s)]);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup_get(char *s, int to_free)
{
	char	*result;
	size_t	len;

	len = ft_strlen_get((char *)s) + 1;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (0);
	result = ft_memmove_get(result, s, len);
	if (to_free == 1)
		free(s);
	return (result);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	totlen;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup_get((char *)s1, 1));
	if (!s1 && s2)
		return (ft_strdup_get((char *)s2, 0));
	s1_len = ft_strlen_get((char *)s1);
	s2_len = ft_strlen_get((char *)s2);
	totlen = s1_len + s2_len + 1;
	result = malloc(sizeof(char) * totlen);
	if (!result)
	{
		free ((void *) s1);
		return (0);
	}
	ft_memmove_get(result, s1, s1_len);
	ft_memmove_get(result + s1_len, s2, s2_len);
	result[totlen - 1] = '\0';
	free (s1);
	return (result);
}

void	*ft_memmove_get(void *dest, void *src, size_t n)
{
	size_t			i;
	unsigned char	*srccpy;
	unsigned char	*destcpy;

	destcpy = (unsigned char *)dest;
	srccpy = (unsigned char *)src;
	i = 0;
	if (src < dest)
	{
		while (n--)
		{
			destcpy[n] = srccpy[n];
		}
		return (dest);
	}
	else
	{
		while (i < n)
		{
			destcpy[i] = srccpy[i];
			i++;
		}
	}
	return (dest);
}
