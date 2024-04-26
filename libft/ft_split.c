/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:07:48 by mlapique          #+#    #+#             */
/*   Updated: 2024/04/15 14:55:30 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	newsplit(char **result, char *s, int i, int ind)
{
	int	start;

	start = i;
	i++;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			result[ind] = ft_substr(s, start, i - start + 1);
			result[ind] = ft_strtrim(result[ind], "\'");
			return (i - start + 1);
		}
		i++;
	}
	return (0);
}

static int	ft_count(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] == '\'')
		{
			word++;
			i++;
			while (s[i] != '\'')
				i++;
		}
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static void	freememory(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

static char	**spliting(char **result, int i, char c, char *s)
{
	int	start;
	int	ind;

	ind = 0;
	start = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
		{
			i += newsplit(result, s, i, ind);
			start = i + 1;
			ind++;
			if (s[i] == '\0')
				return (result[ind] = NULL, result);
		}
		if (s[i] == c)
			start = i + 1;
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			result[ind] = ft_substr(s, start, i - start + 1);
			if (result[ind++] == NULL)
				return (freememory(result), NULL);
		}
	}
	return (result[ind] = NULL, result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), (ft_count((char *)s, c) + 1));
	if (!result)
		return (NULL);
	result = spliting(result, i, c, (char *)s);
	return (result);
}
