#include "get_next_line.h"

char *ft_BeforeEq(char *k)
{
    int i=0;
    int j=0;
    char *str;
    str = malloc(sizeof(char)*strlen(k));

    while(k[i])
    {
        if(k[i] == '=')
        {
            str[i] = 0;
            break;
        }
        str[i] = k[i];
        i++;
    }
    return str;
}

char *ft_remove_quotes_two(char *buf)
{
    int i = 0;
    int cpt = 0;
    int startquotes,endquotes;
    int start_dquotes,end_dquotes;
    int start = 0,end;
    char *ptr = ft_strdup("");
    while(buf[i])
    {
        if(buf[i] == '\'')
        {
            if(cpt == 0)
            {
                cpt = 1;
                startquotes = i + 1;
                ptr = ft_strjoin(ptr, ft_substr(buf,start,i - start));
            }
            else if(cpt == 1)
            {
                start = i + 1;
                endquotes = i;
                cpt = 0;
                ptr = ft_strjoin(ptr, ft_substr(buf,startquotes,endquotes - startquotes));
            }
        }
        else if(buf[i] == '"')
        {
            if(cpt == 0)
            {
                cpt = 2;
                start_dquotes = i + 1;
                ptr = ft_strjoin(ptr, ft_substr(buf,start,i - start));
                //printf("%d\n",startquotes);
            }
            else if(cpt == 2)
            {
                start = i + 1;
                end_dquotes = i;
                cpt = 0; 
                //printf("%d| %d|\n",start_dquotes,end_dquotes);
                ptr = ft_strjoin(ptr, ft_substr(buf,start_dquotes,end_dquotes - start_dquotes));
                
            }
        }
        i++;
    }
    if (buf[start] != '\0')
        ptr = ft_strjoin(ptr, ft_substr(buf,start,i));
    return ptr;
}
char *ft_BeforeEq_two(char *k)
{
    int i=0;
    int j=0;
    char *str;
    str = malloc(sizeof(char)*strlen(k));
   
    while(k[i])
    {
        if(k[i] == ' ')
        {
            printf("error\n");
            return ft_strdup("");
        }
        if(k[i] == '=')
        {
            str[i] = 0;
            break;
        }
        str[i] = k[i];
        i++;
    }
    str[i] = '\0';
    return str;
}

char *ft_AfterEq(char *k)
{
    int i=0;
    int j = 0;
    char *str;
    str = malloc(sizeof(char)*strlen(k));
    if(strstr(k,"PATH") != NULL)
    {
        path = strstr(k,"PATH");
        path2 = ft_split(&path[5],':');
        while(path2[i])
        {
            path2[i] = ft_strjoin(path2[i],"/");
            i++;
        }
    }
    i = 0;
    while(k[i])
    {
        if(k[i] == '=')
        {
            i++;
             while(k[i] == ' ')
                 i++;
            break;
        }
        i++;
    }
    str = k+i;
    return str;

}