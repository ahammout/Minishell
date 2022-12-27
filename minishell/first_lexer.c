/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/27 19:09:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // INCLUDE THE QUOTING ON THE LEX STRING.

int lexer(t_data *data)
{
    int         i;
    int         add_node;
    t_tokens    *tmp;
    t_tokens    *to_free;

    i = 0;
    add_node = 0;
    data->tokens = malloc(sizeof(t_tokens));
    if (!data->tokens)
        exit_error(data, 1, "Minishell: Allocation failed.");
    data->tokens->next = NULL;
    tmp = data->tokens;
    to_free = tmp;
    while (data->buffer[i])
    {
        if (data->buffer[i] == ' ' || data->buffer[i] == '\t')
            while(data->buffer[i] == ' ' || data->buffer[i] == '\t')
                i++;
        else if (data->buffer[i] != ' ' && data->buffer[i] != '\t' && data->buffer != '\0')
        {
            if (data->buffer[i] == SQUOTE)
            {
                if (add_node)
                {
                    add_new_node (data, tmp);
                    tmp = tmp->next;
                }
                i += quotes (data, data->buffer + i, tmp, SQUOTE);
                add_node = 1;
            }
            else if (data->buffer[i] == DQUOTE)
            {
                if (add_node)
                {
                    add_new_node (data, tmp);
                    tmp = tmp->next;
                }
                i += quotes (data, data->buffer + i, tmp, DQUOTE);
                add_node = 1;
            }
            else if (data->buffer[i] == ESCAP)
            {
                if (add_node)
                {
                    add_new_node (data, tmp);
                    tmp = tmp->next;
                }
                i += escap (data, data->buffer + i, tmp);
                add_node = 1;
            }

            // REDIRECTION / APPEND OUTPUT  [File comes after those].
            else if (data->buffer[i] == REDOUT)
            {
                if (add_node)
                {
                    add_new_node (data, tmp);
                    tmp = tmp->next;
                }
                i += operator(data, data->buffer + i, tmp, REDOUT);
                add_node = 1;
            }

            // REDIRECTION / APPEND INPUT.
            else if (data->buffer[i] == REDIN)
            {
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += operator(data, data->buffer + i, tmp, REDIN);
                add_node = 1;
            }
        
            /// OPERATIONAL OPERATORS.
            else if (data->buffer[i] == SEPERATOR)
            {
                // Sep case
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += operator(data, data->buffer + i, tmp, SEPERATOR);
                add_node = 1;

            }
            else if (data->buffer[i] == PIPE)
            {
                // Pipe case
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += operator(data, data->buffer + i, tmp, PIPE);
                add_node = 1;
            }
            else if (data->buffer[i] == EXPAND_)
            {
                // variable case
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += operator(data, data->buffer + i, tmp, VARIABLE_);
                add_node = 1;
            }
            else
            {
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += keyword(data, data->buffer + i, tmp);
                add_node = 1;
            }
        }
    }
    display_list(data);
    free_tmp(to_free);
    return (0);
}

/// Freeing the buffer when finish using it / affecting it by NULL.
