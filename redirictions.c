#include "get_next_line.h"

void double_redr(char *str, char **ptr, int *start, int *i)
{
    *ptr =ft_strjoin(*ptr,ft_substr(str,*start,*i - *start));
    *i = *i + 2;
    while(str[*i] == ' ' && str[*i])
        *i = *i + 1;
    g_red_start = *i;
    ft_remove_quotes_file(str,i);
    g_fd = open(g_red_buff,O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0777);
    g_red_buff = ft_strdup("");
    dup2(g_fd,1);
    *start = *i;
}

void    single_redr(char *str, char **ptr, int *start, int *i)
{
    *ptr = ft_strjoin(*ptr,ft_substr(str,*start,*i - *start));
    *i = *i + 1;
    while(str[*i] == ' ' && str[*i])
        *i = *i + 1;
    g_red_start = *i;
    ft_remove_quotes_file(str,i);
    g_fd = open(g_red_buff,O_TRUNC | O_WRONLY | O_CREAT,0777);
    g_red_buff = ft_strdup("");
    dup2(g_fd,1);
    *start = *i;
}

void    check_readrd(char *str, char **ptr, int *start, int *i)
{
    *ptr = ft_strjoin(*ptr,ft_substr(str,*start,*i - *start));
    *i = *i + 2;
    while(str[*i] == ' ' && str[*i])
        *i = *i + 1;
    g_red_start = *i;
    ft_remove_quotes_file(str,i);
    g_fd = open(g_red_buff,O_RDONLY,0777);
    g_red_buff = ft_strdup("");
    *start = *i;
    dup2(g_fd,0);
    g_read = 1;
}

char *ft_check_redr(char *str,int cpt)
{
    int i = 0;
    int start = 0;
    int end=0;
    char *ptr=ft_strdup("");
    g_red_buff = ft_strdup("");
    while(str[i])
    {    
        while(str[i] == '>' && str[i] != '\0')
        {
            if(str[i] == '>' && str[i+1] == '>')
                double_redr(str, &ptr, &start, &i);
            if(str[i] == '>' && str[i+1] != '>')
                single_redr(str, &ptr, &start, &i);
        }
        if(str[i] == '<')
            check_readrd(str, &ptr, &start, &i);
        i = i + 1;
    }
    ptr = ft_strjoin(ptr,ft_substr(str,start,i - start));
    free(split[cpt]);
    split[cpt] = ft_strdup(ptr);
    return ptr;
}