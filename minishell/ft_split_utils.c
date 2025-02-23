/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:15:28 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/21 22:25:56 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_split(char **result)
{
	int	j = 0;

	if (result)
	{
		while (result[j])
		{
			free(result[j]);
			j++;
		}
		free(result);
	}
	return (0);
}

int	process_token(char **s_ptr, char delim, char **token)
{
	char	*s;
	char	*end;

	s = *s_ptr;
	end = find_token_end(s, delim);
	if (end > s)
	{
		*token = ft_allocate_quotes(s, end);
		if (!*token)
			return (0);
	}
	*s_ptr = end;
	return (1);
}

void	update_word_state(const char ch, char delim,
		int *in_quotes, char *quote, int *in_word, int *words)
{
	if (!(*in_quotes) && (ch == '\'' || ch == '\"'))
	{
		*in_quotes = 1;
		*quote = ch;
		if (!(*in_word))
		{
			(*words)++;
			*in_word = 1;
		}
	}
	else if (*in_quotes && ch == *quote)
		*in_quotes = 0;
	else if (!(*in_quotes) && ch == delim)
		*in_word = 0;
	else if (!(*in_word))
	{
		(*words)++;
		*in_word = 1;
	}
}

char	*allocate_remove_all_quotes(char *start, char *end)
{
	int		len;
	char	*p;
	char	*str;
	int		i;

	len = 0;
	p = start;
	while (p < end)
	{
		if (*p != '\'' && *p != '\"')
			len++;
		p++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		if (*start != '\'' && *start != '\"')
			str[i++] = *start;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_allocate_quotes(char *start, char *end)
{
	if (start < end && (*start == '\'' || *start == '\"') && *(end - 1) == *start)
		return (allocate_outer_quotes(start, end));
	else
		return (allocate_remove_all_quotes(start, end));
}