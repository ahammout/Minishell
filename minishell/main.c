/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/27 18:22:45 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     i;
    int     buffer_size;

    data.buffer = ft_strdup("");
    data.envp_ = envp; 
    (void)ac;
    av = NULL;
    i = 0;
    buffer_size = 0;
    while (1)
    {
        //// Reading the input line
        while (buffer_size == 0)
        {
            free(data.buffer);
            data.buffer = readline("minishell $> ");
            buffer_size = ft_strlen(data.buffer);
        }
        // while (envp[i])
        //     printf("%s\n", envp[i++]);

        /// LEXER : TOKENAZING THE INPUT.
        lexer(&data);
        
        ////// CHECK THE SYNTAX : GENERATE ERRORS / GENERATE VALID COMMAND ///////
        /* 
            RETURN : SECCUES : + VALID SYNTAX ==> LINKED LIST[TOKENAZED].
                     FAILURE : + INVALID SYNTAX ==> ERROR MESSAGE & EXIT FAILURE.
        */
        syntax_checker (&data);
        
        free_data(&data);
        buffer_size = 0;
    }
}
