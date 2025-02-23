/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/22 23:48:41 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	char *rl;
	t_token *token;

	(void)argv;
	sig_int_handler();
	sig_ign_handler();
	if (argc == 1)
	{
	    while(1)
	    {
	        rl = readline("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37m");
			if (!rl)
			{
				printf("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37mexit\n");
			    break;
			}
			token = ft_add_cmd(rl);
			t_parse *cmd = ft_parse_pipe(&token);
			t_parse *tmp = cmd;
			while(tmp)
			{
				printf("%s -- ", tmp->cmd_name);
				if (tmp->args) 
				{
				    for (int i = 0; tmp->args[i]; i++)
				        printf("%s ", tmp->args[i]);
				}
				printf("-- %s -- %s -- %d\n", tmp->in_re, tmp->out_re, tmp->app);
				tmp = tmp->next;
			}
		}
	}
    return (0);
}
