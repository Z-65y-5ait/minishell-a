/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 03:10:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/22 00:30:56 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (lst && new)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			head = ft_lstlast((*lst));
			head->next = new;
		}
	}
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*head;

	if (lst && new)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			head = ft_lstlast_token((*lst));
			head->next = new;
		}
	}
}