#include "get_next_line.h"

int    stock_squotes(char *str, int *i, int cpt)
{
    *i = *i +1;
    while(str[*i] != '\'' && str[*i] != '\0')
        *i = *i +1;
    if(str[*i] != '\0')
        *i = *i +1;
    else
    {
        split[cpt] = ft_substr(str,g_start,*i - g_start - 1);
        g_start = *i + 1;
        return 0;
    }
    return 1;
}

int    stock_dquotes(char *str, int *i, int cpt)
{
    *i = *i +1;
    while(str[*i] != '"' && str[*i] != '\0')
        *i = *i +1;
    if(str[*i] != '\0')
        *i = *i +1;
    else
    { 
        split[cpt] = ft_substr(str,g_start,*i - g_start - 1);
        g_start = *i + 1;
        return 0;
    }
    return 1;
}

int     stock_last(char *str, int *i, int cpt)
{                
    split[cpt] = ft_substr(str,g_start,*i - g_start);
    g_start = *i + 1;
    *i = *i + 1;
    return 0;
}

void ft_stock_split(char *str, int *i,int cpt)
{
    while(str[*i])
    {
        if(str[*i] == '\'' && (stock_squotes(str, i, cpt) == 0))
            break;
        if(str[*i] == '"' && (stock_dquotes(str, i, cpt) == 0))
            break;
        if(str[*i] == ';' &&  (stock_last(str, i, cpt) == 0))
            break;
        *i = *i +1;
    }
}