/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 04:08:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/21 22:23:50 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *s, char c)
{
	int		words;
	int		in_word;
	int		in_quotes;
	char	quote;

	words = 0;
	in_word = 0;
	in_quotes = 0;
	quote = '\0';
	if (!s)
		return (0);
	while (*s)
	{
		update_word_state(*s, c, &in_quotes, &quote, &in_word, &words);
		s++;
	}
	return (words);
}

char	*allocate_outer_quotes(char *start, char *end)
{
	int		len;
	char	*str;
	int		i;

	len = end - start - 2;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = start[i + 1];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*find_token_end(char *s, char delim)
{
	int		in_quotes;
	char	quote;

	in_quotes = 0;
	quote = '\0';
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote = *s;
			}
			else if (*s == quote)
				in_quotes = 0;
		}
		else if (!in_quotes && *s == delim)
			break ;
		s++;
	}
	return (s);
}

static int	ft_all(char *s, char delim, char **ptr)
{
	int	i = 0;

	while (*s)
	{
		while (*s && *s == delim)
			s++;
		if (!*s)
			break ;
		if (!process_token(&s, delim, &ptr[i]))
			return (free_split(ptr));
		i++;
		while (*s && *s == delim)
			s++;
	}
	ptr[i] = NULL;
	return (1);
}


char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	if (!ft_all((char *)s, c, ptr))
		return (NULL);
	return (ptr);
}
