#include "get_next_line.h"

void    remove_sqfile(char *str,int *i)
{
    int start_sq;

    g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));
    start_sq = *i + 1;
    while (str[*i] != '\'' && str[*i] != '\0')
        *i = *i + 1;
    g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,start_sq,*i - start_sq));
    *i = *i + 1;
    g_red_start = *i;
}

void    remove_dqfile(char *str, int *i)
{
    int start_dq;

    g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));
    start_dq = *i + 1;          
    while (str[*i] != '"' && str[*i] != '\0')
        *i = *i + 1;
    g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,start_dq,*i - start_dq));
    *i = *i + 1;
    g_red_start = *i;
}

void ft_remove_quotes_file(char *str,int *i)
{
    while(str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i])
    {
        if(str[*i] == '\'')
            remove_sqfile(str, i);
        else if(str[*i] == '"')
            remove_dqfile(str, i);
        else
        {
            if(str[*i] != '\0')
                *i = *i + 1;
        }         
    }
    if (g_red_start != ft_strlen(str))
        g_red_buff  = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));  
}