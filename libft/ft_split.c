/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:56:52 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/09 12:57:18 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	can_cpy(char **res, int index, size_t len)
{
	int	i;

	i = 0;
	res[index] = malloc(len);
	if (!res[index])
	{
		while (i < index)
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (1);
	}
	return (0);
}

static int	cpy_str(char **res, const char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s != '\0')
	{
		len = 0;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (can_cpy(res, i, len + 1))
				return (1);
			ft_strlcpy(res[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		in_word;

	words = 0;
	while (*s != '\0')
	{
		in_word = 0;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			if (!in_word)
			{
				words++;
				in_word = 1;
			}
			s++;
		}
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	size_t	num_words;
	char	**result;

	if (!s)
		return (NULL);
	num_words = 0;
	num_words = count_words(s, c);
	result = malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[num_words] = NULL;
	if (cpy_str(result, s, c))
		return (NULL);
	return (result);
}
/*
int main(void)
{
	char	*str = "hello everyone my name is saeed!";
	char	**result;
	int	i;
	
	result = ft_split(str, ' ');
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	free(result);	
}
*/
