/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:18:57 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/25 20:34:53 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_new(t_token_type type, void *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_parse	*ft_parse_new(void)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->cmd_name = NULL;
	new->args = NULL;
	new->in_re = -2;
	new->out_re = -2;
	new->builtins = 0;
	new->next = NULL;
	return (new);
}