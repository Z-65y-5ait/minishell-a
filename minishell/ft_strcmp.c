/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:07:57 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/24 17:10:11 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] || p2[i]))
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] > p2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}