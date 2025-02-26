/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:12:15 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/26 02:42:57 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_add_cmd(char *rl)
{
	int i;
    char **buff;
    t_token *lst;

	i = 0;
    buff = ft_split(rl, ' ');
	free(rl);
	lst = NULL;
    while(buff[i] != NULL)
	{
		if (ft_strncmp(buff[i], "|", 1) == 0)
        	ft_lstadd_back_token(&lst, ft_token_new(T_PIPE, buff[i++]));
		else if (ft_strncmp(buff[i], "<<", 2) == 0)
        	ft_lstadd_back_token(&lst, ft_token_new(T_HERDOC, buff[i++]));
		else if (ft_strncmp(buff[i], ">>", 2) == 0)
        	ft_lstadd_back_token(&lst, ft_token_new(T_APPEND, buff[i++]));
		else if (ft_strncmp(buff[i], "<", 1) == 0)
        	ft_lstadd_back_token(&lst, ft_token_new(T_REDIR_IN, buff[i++]));
		else if (ft_strncmp(buff[i], ">", 1) == 0)
        	ft_lstadd_back_token(&lst, ft_token_new(T_REDIR_OUT, buff[i++]));
		else
        	ft_lstadd_back_token(&lst, ft_token_new(T_WORD, buff[i++]));
	}
    free(buff);
	return (lst);
}

t_parse	*ft_parsing(t_token **token)
{
	int i;
	char	**arg;
	char	**ar;
	t_parse *parse;

	i = 0;
	parse = ft_parse_new();
	if (!parse)
		return (NULL);
	arg = ft_check_parse(token, &parse, &i);
	if (!arg)
        return (NULL);
	parse->args = arg;
	if (i > 0)
		parse->cmd_name = ft_strdup(arg[0]);
	else
        parse->cmd_name = NULL;
	ft_builtins_check(parse);
	return (parse);
}

static void	handle_redirection(t_token **check, t_parse **p)
{
	int fd;
	t_token_type	type;
	t_token *redirect_token;

    redirect_token = *check;
	type = redirect_token->type;
	*check = redirect_token->next;
	if (!*check)
		return ;
	if (type == T_REDIR_IN)
	{
		fd = open((*check)->value, O_RDONLY);
		(*p)->in_re = fd;
	}
	else if (type == T_REDIR_OUT)
	{
		fd = open((*check)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*p)->out_re = fd;
	}
	else if (type == T_APPEND)
	{
		fd = open((*check)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		(*p)->out_re = fd;
	}
	*check = (*check)->next;
}

char	**ft_check_parse(t_token **check, t_parse **p, int *i)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 101);
	if (!arg)
		return (NULL);
	while ((*check) && ((*check)->type != T_PIPE))
	{
		if ((*check)->type == T_REDIR_IN || (*check)->type == T_REDIR_OUT
			|| (*check)->type == T_APPEND)
		{
			handle_redirection(check, p);
			cleanup_redirections(*p);
		}
		else if ((*check)->type == T_WORD)
		{
			arg[(*i)++] = ft_strdup((*check)->value);
			(*check) = (*check)->next;
		}
		else
			(*check) = (*check)->next;
	}
	arg[*i] = NULL;
	return (arg);
}

static t_parse *parse_piped_commands(t_token **token_p)
{
    t_parse *cmd;
	t_token *token;
	t_parse *next_cmd;

	cmd = ft_parsing(token_p);
    if (!cmd)
        return NULL;
    token = *token_p;
    if (token && token->type == T_PIPE)
    {
        *token_p = token->next;
        next_cmd = parse_piped_commands(token_p);
        if (!next_cmd)
            return NULL;
        cmd->next = next_cmd;
    }
    else
        *token_p = token;
    return cmd;
}

t_parse *ft_parse_pipe(t_token **token_p)
{
    return (parse_piped_commands(token_p));
}

int validate_pipes(t_token *token)
{
    int expect_command;

	expect_command = 1;
    while (token)
    {
        if (token->type == T_PIPE)
        {
            if (expect_command)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return 0;
            }
            expect_command = 1;
        }
        else
            expect_command = 0;
        token = token->next;
    }
    if (expect_command)
    {
        printf("minishell: syntax error: unexpected end of file\n");
        return 0;
    }
    return 1;
}
