#include "get_next_line.h"

int    ft_checkQuotes(int *i,int *cpt,int *cpt2,char *s)
{
    if(s[*i] == '\'')
    {
        *cpt =1;
        *i = *i + 1;
    }
    else if(s[*i] == '"')
    {
        *cpt2 =1;
        *i = *i + 1;
    }
    return *i;
}
void    ft_storeData(char *s,char **str,int start,int i,char **env)
{
    char *test = ft_strjoin(*str,ft_substr(s,start,i-start));
    if(s[i] == '\'')
    {
        *str = ft_strjoin(*str,ft_substr(s,start,i-start));
    }   
    else
    {
        *str = ft_checkDollar(test,env);
    }        
}

char *ft_remove_spaces(char *haha, int *start, int *i)
{
    // printf("ok\n");
    // exit(0);
    char *ptr;
    while((haha[*start] == ' ' || haha[*start] == '\t') && haha[*start] != '\0')
        *start = *start + 1;
    *i = *start;
    while(haha[*i] != ' ' && haha[*i] != '\t' && haha[*i] != '\0')
        *i = *i + 1;
    ptr =  ft_substr(haha,*start,*i - *start);
    while((haha[*i] == ' ' || haha[*i] == '\t') && haha[*i] != '\0')
        *i = *i + 1;
    *start = *i;
    // printf("kokk\n");
    // exit(0);
    return ptr;
}

void ft_get_between_spaces(char *haha,int *i,int *start,char **ptr)
{
    int end;
    while(haha[*i] != ' ' && haha[*i] != '\'' && haha[*i] != '"' && haha[*i] != '\0')
        *i = *i + 1;
    end = *i;
    *ptr = ft_strjoin(*ptr, ft_substr(haha,*start,end - *start));
    while((haha[*i] == ' ' || haha[*i] == '\t') && haha[*i] != '\0')
        *i = *i + 1;
    if(haha[*i] != '\0' && haha[*i] != '\'' && haha[*i] != '"')
        *ptr = ft_strjoin(*ptr," ");
    else if(haha[*i] == '\'' || haha[*i] == '"')
    {
        if(haha[*i - 1] == ' ')
            *ptr = ft_strjoin(*ptr," ");
    }
    *start = *i;   
}

void ft_get_between_slash(char *haha,int *i,int *start,char **ptr)
{
    int end;
    int start_slash = 0;

    
    while(haha[*i] != '\\' && haha[*i] != '\0')
        *i = *i + 1;
    end = *i;
    *ptr = ft_strjoin(*ptr, ft_substr(haha,*start,end - *start));
    // while((haha[*i] == '\\') && haha[*i] != '\0')
    // {
    //     start_slash++;
    //     *i = *i + 1;
    // }
       
    // if( start_slash > 1)
    // {
    //     int x = 0;
    //     while(x < start_slash / 2)
    //     {
    //         *ptr = ft_strjoin(*ptr,"\\");
    //         x++;
    //     }
    // }
    // else if(start_slash == 1)
    // {
    //     i++;
    // }
    // if ((start_slash % 2) != 0 && haha[*i] == ' ' && start_slash != 0)
    //         *ptr = ft_strjoin(*ptr," ");
    //printf("str |%c%c|\n",haha[*i],haha[*i + 1]);
    // if(haha[*i] != '\0' && haha[*i] != '\'' && haha[*i] != '"')
    //     *ptr = ft_strjoin(*ptr," ");
    *start = *i;   
}