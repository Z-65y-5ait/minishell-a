/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:43:49 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/26 01:54:52 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_redirections(t_parse *p)
{
    if (p->in_re == -1)
		close(p->in_re);
    if (p->out_re == -1)
		close(p->out_re);
}

void	ft_builtins_check(t_parse *par)
{
	if (par->cmd_name && (f_strcmp(par->cmd_name, "echo") == 0)
		|| f_strcmp(par->cmd_name, "cd") == 0
		|| f_strcmp(par->cmd_name, "pwd") == 0
		|| f_strcmp(par->cmd_name, "export") == 0
		|| f_strcmp(par->cmd_name, "unset") == 0
		|| f_strcmp(par->cmd_name, "env") == 0
		|| f_strcmp(par->cmd_name, "exit") == 0)
		par->builtins = 1;
	else
		par->builtins = 0;
}

// void free_parse(t_parse *cmd)
// {
//     t_parse *tmp;
//     t_parse *next;
//     int i;

//     tmp = cmd;
//     while (tmp)
//     {
//         next = tmp->next;
//         if (tmp->cmd_name)
//         {
//             free(tmp->cmd_name);
//             tmp->cmd_name = NULL;
//         }
//         if (tmp->args)
//         {
//             i = 0;
//             while (tmp->args[i])
//             {
//                 free(tmp->args[i]);
//                 tmp->args[i] = NULL;
//                 i++;
//             }
//             free(tmp->args);
//             tmp->args = NULL;
//         }
//         free(tmp);
//         tmp = next;
//     }
// }
