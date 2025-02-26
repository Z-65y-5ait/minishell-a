/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/26 02:15:21 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(char *rl)
{
	
}

void	minishell_loop()
{
	char *rl;
	t_parse *cmd;
	t_token *token;
	t_error_type state;

	while(1)
    {
        rl = readline("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37m");
		if (!rl)
		{
			printf("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37mexit\n");
		    break;
		}
		add_history(rl);
		token = ft_add_cmd(rl);
		cmd = ft_parse_pipe(&token);
		if (!cmd)
			continue;
		ft_print_list(cmd);
	}
}

		// if (!cmd || !cmd->cmd_name)
		// {
		//     printf("minishell: Syntax error near `|'\n");
		//     continue;
		// }
		// state = ft_handle_error(cmd, rl);
		// if (state == ERR_EMPTY_SYNTAX)
		// {
		// 	printf("minishell: Syntax error near `|'\n");
		// 	// free(rl);
		// 	continue;
		// }
		// else if (state == ERR_UNCLOSED_QUOTES)
		// {
		// 	printf("minishell: Syntax error: Unclosed quotes\n");
		// 	// free(rl);
		// 	continue;
		// }
		// else if (state == ERR_TOO_MANY_ARGS)
		// {
		// 	printf("minishell: Syntax error: Too many arguments\n");
        //     // free_parse(cmd);
		// 	continue;
		// }
		// else if (state == ERR_PIPE_SYNTAX)
		// {
		// 	printf("minishell: Syntax error: empty command\n");
		// 	continue;
		// }
		// else if (state == ERR_SYNTAX)
		// {
		// 	printf("minishell: syntax error near unexpected token '|'\n");
        //     // free_parse(cmd);
		// 	continue;
		// }
		
		// free(rl);
		// free_parse(cmd);
// 	}
// }

void	ft_print_list_2(t_token *cmd)
{
	t_token *tmp;
	
	tmp = cmd;
	while(tmp)
	{
		printf("-- %s -- %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}

void ft_print_list(t_parse *cmd)
{
    int i;
    t_parse *tmp;
    
    tmp = cmd;
    while (tmp)
    {
        i = 0;
        if (tmp->cmd_name)
            printf("%s -- ", tmp->cmd_name);
        else
            printf("(no command) -- ");
        if (tmp->args) 
        {
            while (tmp->args[i])
            {
                printf("%s ", tmp->args[i]);
                i++;
            }
        }
        printf("-- %d -- %d -- %d\n", tmp->in_re, tmp->out_re, tmp->builtins);
        tmp = tmp->next;
    }
}

int main(int argc, char **argv)
{
	(void)argv;
	sig_int_handler();
	sig_ign_handler();
	if (argc == 1)
		minishell_loop();
    return (0);
}
