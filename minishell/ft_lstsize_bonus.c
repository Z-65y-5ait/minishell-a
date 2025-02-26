/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:53:40 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/24 16:20:44 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*head;

	head = lst;
	count = 1;
	if (!lst)
		return (0);
	while (head->next != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	ft_lstsize_token(t_token *token)
{
	int		count;
	t_token	*head;

	head = token;
	count = 1;
	if (!token)
		return (0);
	while (head != NULL && head->type == T_WORD)
	{
		count++;
		head = head->next;
	}
	return (count);
}