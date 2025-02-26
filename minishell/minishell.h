/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/26 01:58:43 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libc.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef enum e_token
{
		T_WORD,
		T_PIPE,
		T_REDIR_IN,
		T_REDIR_OUT,
		T_APPEND,
		T_HERDOC,
}	t_token_type;

typedef enum e_quotes
{
		NONE,
		S_QUOTES,
		D_QUOTES,
}	t_quotes_state;

typedef enum e_error
{
		ERR_NONE,
		ERR_SYNTAX,
		ERR_NO_FILE,
		ERR_NUM_ARG,
		ERR_PIPE_SYNTAX,
		ERR_EMPTY_SYNTAX,
		ERR_TOO_MANY_ARGS,
		ERR_INVALID_OPTION,
		ERR_UNCLOSED_QUOTES,
		ERR_PERMISSION_DENIED,
}	t_error_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char			*cmd_name;
	char			**args;
	int				in_re;
	int				out_re;
	int				builtins;
	struct s_parse	*next;
}	t_parse;

char			**ft_split(char const *s, char c);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstnew(void *content);
int				free_split(char **result);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_lstsize(t_list *lst);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				process_token(char **s_ptr, char delim, char **token);
void			update_word_state(const char ch, char delim,
				int *in_quotes, char *quote, int *in_word, int *words);
char			*find_token_end(char *s, char delim);
char			*allocate_outer_quotes(char *start, char *end);
char			*allocate_remove_all_quotes(char *start, char *end);
char			*ft_allocate_quotes(char *start, char *end);
t_token			*ft_token_new(t_token_type type, void *content);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
t_token			*ft_lstlast_token(t_token *lst);
void			sig_ign_handler(void);
void			sig_int_handler(void);
t_parse			*ft_parsing(t_token **token);
t_parse			*ft_parse_new(void);
char			*ft_strdup(char *s);
t_token 		*ft_add_cmd(char *rl);
t_parse			*ft_parse_pipe(t_token **token_p);
char			**ft_check_parse(t_token **check, t_parse **p, int *i);
int				ft_lstsize_token(t_token *token);
void			cleanup_redirections(t_parse *p);
void			ft_builtins_check(t_parse *par);
int				f_strcmp(const char *s1, const char *s2);
t_quotes_state	ft_handle_quotes(char *rl);
// void			free_parse(t_parse *cmd);
t_error_type	ft_handle_error(t_parse *cmd, char *rl);
void			ft_print_list(t_parse *cmd);
int				ft_handle_arg(t_parse *cmd);
t_error_type	ft_handle_pipe(t_parse *cmd);
t_error_type 	validate_pipe_syntax(char *input);
size_t			ft_strlen(char *str);
char			*ft_strtrim(char *s1, char *set);
void			ft_print_list_2(t_token *cmd);

#endif