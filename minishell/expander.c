#include "minishell.h"

int size_update(t_data *data, char *temp, char *value)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\0' && temp[i] != data->token->type)
                i++;
        }
        if (temp[i] != '\0')
        {
            len++;
            i++;
        }
    }
    return (len + ft_strlen(value));
}

/// EX : This is the PWD var : $PWD from the env.
void    merge(t_data *data, char *value)
{
    char    *temp;
    int     i;
    int     j;
    int     v;

    temp = data->token->lex;
    free(data->token->lex);
    exit (0);
    printf("NEW SIZE :%d \n", size_update(data, temp, value));
    data->token->lex = malloc(sizeof(char) * size_update(data, temp, value));
    if (!data->token->lex)
    {
        free(temp);
        exit_error(data, 2, "Minishell: Allocation failed.");
    }
    i = 0;
    j = 0;
    v = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t' &&  temp[i] != '\0' && temp[i] != data->token->type)
                i++;
            while (value[v])
                data->token->lex[j++] = value[v++];
        }
        if (temp[i] != '\0')
            data->token->lex[j++] = temp[i++];
    }
    data->token->lex[j] = '\0';
}

char    *get_value(t_data *data, char *var)
{
    int i;
    int j;
    int v;

    i = 0;
    while (data->envp_[i])
    {
        j = 0;
        v = 0;
        while (data->envp_[i][j] != '=')
        {
            if (data->envp_[i][j] != var[v])
                break;
            j++;
            v++;
        }
        if (data->envp_[i][j++] == '=')
            return (data->envp_[i] + j);
        i++;
    }
    return (0);
}

char    *get_var(t_data *data, char *buff)
{
    int     i;
    char    *var;

    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0' && buff[i] != data->token->type)
        i++;
    var = malloc(sizeof(char) * i);
    if (!var)
        exit_error(data, 2, "Minishell: Allocation failed.");
    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' &&  buff[i] != '\0' && buff[i] != data->token->type)
    {
        var[i] = buff[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}


// int expander (t_data *data, char *buff)
// {
//     int     d;
//     int     i;
//     char    *var;
//     char    *value;

//     d = 0;
//     var = NULL;
//     while (buff[d] == EXPAND_)
//         d++;
//     if (buff[d] != ' ' && buff[d] != '\t')
//     {
//         // if (buff[i] == '?')
//         //     get_exit_status(data, buff + i);
//         var = get_var (data, buff + d);
//         value = get_value (data, var);
//         if (value != NULL)
//             merge(data, value);
//         /// if variable not exist.
//         /// don't dispay it
//     }
//     free  (var);
//     return (i);
// }

// void    quotes_exp(char *buff);

/*
    $$$$@
*/

// int is_silent(char c)
// {
//     if (ft_isdigit(c) || c == '@')
//         return (1);
//     return (0);
// }

// void    behind_silent(char *buff, int d)
// {
//     int i;

//     i = 1;
//     while (buff[i])
//     {
        
//     }
// }



int update_size(int size_pid, char *temp)
{
    int d;
    int i;

    while (temp[i])
    {
        if (temp[i++] == EXPAND_)
            d++;
        i++;
    }
}

int handle_dolar(t_data *data, int index, char pid)
{
    char    *temp;
    int     i;

    i = 0;
    temp = data->token->lex;
    free(data->token->lex);
    data->token->lex = malloc(sizeof (char) * update_size(ft_strlen(pid), temp));
    while (temp[i])
    {
        
    }

}

//// lexem = adfsfsfrfer$$$$$$@HOME.

int expander (t_data *data, char *buff)
{
    int     d;
    char    *pid;
    char    *var;
    char    *value;

    d = 0;
    var = NULL;
    value = NULL;
    pid = ft_itoa(getppid());
    d += handle_dolar (data, d, pid);
    // // Check if expanded.
    // // $$$HOME_
    // if (d % 2 != 0 && buff[d] != '\0')
    // {
    //     // CASE OF '@' & NUMBERS
    //     if (is_silent(buff[d]))
    //         behind_silent(data, buff + d);
    //     // ALPHABETIC CASE
    //     else
    //     {
            
    //     }
    // }

    exit (0);  
}