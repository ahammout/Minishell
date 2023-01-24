/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/16 16:32:47 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

/* add list of tokens characters*/
// add operators : AND, OR, ASTERISK, SEMECOLE, TILD.

enum{
    SQUOTE = '\'',
    DQUOTE = '\"',
    REDIN = '<',
    REDOUT = '>',
    APPEND = -124,
    HEREDOC = -120,
    PIPE = '|',
    EXPAND_ = '$',
    SEMICOLONE = ';',
    AND = '&',
    TILD = '~',
    ASTERISK = '*',
    KEYWORD = -1,
};

// typedef struct  s_var
// {
//     char    *name;
//     char    *value;
// }               t_var;


typedef struct  s_tokens
{
    char            *lex;
    int             type;
    int             lenght;
    struct s_tokens  *next;
}               t_tokens;

typedef struct  s_data
{
    char        *buffer;
    char        **envp_;
    t_tokens    *token;
    int         err;
}               t_data;

        ///////// Minshell function principal //////////

int         minishell(t_data *data);

        /////////// LEXER //////////////

t_tokens    *lexer (t_data *data);
int         is_quoted(t_data *data, char *buffer, int *add_node);
int         is_redirection(t_data *data, char *buffer, int *add_node);
int         is_pipe (t_data *data, char *buffer, int *add_node);
int         is_keyword(t_data *data, char *buffer, int *add_node);
int         quotes (t_data *data, char *buff, char quote);
int         expand (t_data *data, char *buff);
int         is_escap (char c);
int         keyword (t_data *data, char *buff);
int         operator (t_data *data, char *buff, int type);
void        optype (int size, int type, t_tokens *token);
int         is_space_or_tab(char *buffer);
void        init_list(t_data *data);
int         non_operator(char c);
void        add_new_node (t_data *data);

        //////// SYNTAX ANALYZER ///////////
t_tokens    *syntax_checker (t_data *data);
int         check_first_end(t_data *data);
int         invalid_begin(t_tokens *token);
int         invalid_end(t_tokens *token);
int         invalid_file(t_tokens *token);
void        check_keyword(t_data *data);
int         quotes_syntax(t_data *data);
int         check_quotes(char *lexem, int type);
void        abs_syntax(t_data *data, int lexem_len, int n_quotes);
int         check_redirections (t_data *data);
int         expand_var(t_data *data);
int         expander (t_data *data, char *buff);
int         is_silent(char c);
void        expand_silent (t_data *data, char *dolars, int exp);
int         update_lexlen(char *buff, char *dolars, int exp);
void        non_param(t_data *data, char *dolars);
void        exp_var(t_data *data, char *buff, char *dolars);
int         size_update(char *temp, char *dolars, char *value);


        /////////////// PARCER ///////////////


        //////////// TOOLS ///////////////
int         non_white(char *str);
void        free_data (t_data *data);
void        exit_error (t_data *data, int option, char *err);
char        **ft_2strdup (char **str);
void        display_list (t_tokens *token);

// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif