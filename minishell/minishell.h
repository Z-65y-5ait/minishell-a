/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/02/22 23:40:21 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CMD 1
#define PIPE 2
#define FILE 3

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
	char			*in_re;
	char			*out_re;
	int				app;
	struct s_parse	*next;
}	t_parse;

char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		free_split(char **result);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_lstsize(t_list *lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		process_token(char **s_ptr, char delim, char **token);
void	update_word_state(const char ch, char delim,
		int *in_quotes, char *quote, int *in_word, int *words);
char	*find_token_end(char *s, char delim);
char	*allocate_outer_quotes(char *start, char *end);
char	*allocate_remove_all_quotes(char *start, char *end);
char	*ft_allocate_quotes(char *start, char *end);
t_token	*ft_token_new(t_token_type type, void *content);
void	ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	*ft_lstlast_token(t_token *lst);
void	sig_ign_handler(void);
void	sig_int_handler(void);
t_parse	*ft_parsing(t_token **token);
t_parse	*ft_parse_new(void);
char	*ft_strdup(char *s);
t_token *ft_add_cmd(char *rl);
t_parse	*ft_parse_pipe(t_token **token_p);
char	**ft_check_parse(t_token **check, t_parse **p, int *i); 

#endif