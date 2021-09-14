
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include "get_next_line.h"
#include <sys/wait.h>


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
char *ft_AfterEq_two(char *k)
{
    int i=0;
    int j = 0;
    char *str;
    
    if(k == 0)
    {
        printf("fariha\n");
        return NULL;
    }
    str = malloc(sizeof(char)*strlen(k));
    while(k[i])
    {
        if(k[i] == '=')
        {
            i++;
            if(k[i] == ' ')
                 return ft_strdup("");
            else if (k[i] == '$')
                return ft_strdup("");
            else if(k[i] == '\0')
                return ft_strdup("");
            break;
        }
        i++;
    }
    if(i == ft_strlen(k))
        return NULL;
    str = k+i;
    return str;
}

void ft_check_redirecitions(char *ptr)
{
    int i = 0;
    while(ptr[i])
    {
        if(ptr[i] == ';')
        {
            g_red = i;
            break;
        }  
    }
}
void    ft_CheckVariables(char *str,char **env,char **stock,int *j)
{
    int i=0,p=0;
    char *s;
    node_t *temp = head; 
    
    while(temp!=NULL)
    {
        if(temp->AfterEq != 0)
        {
            if(strcmp(temp->BeforeEq,str) == 0)
            {
                s = ft_strdup(temp->AfterEq);
                while(s[p])
                {
                    stock[0][*j] = s[p];
                    p++;
                    *j = *j + 1;
                }
                break;
            }
        }         
        temp=temp->next;
    }
}
char *ft_checkDollar(char *str,char **env)
{
    int p=0;
    int j=0;
    int start,end;
    int cpt =0;
    char *stock = malloc(sizeof(char)* 1000);
    int start_slash=0;
    while(str[p])
    {
        start_slash = 0;
        if(str[p] == '\\' && str[p+1] != '/')
        {
            //start_slash = 0;
            while (str[p] == '\\' && str[p+1] != '/')
            {
                stock[j] = str[p];
                j++;
                p++;
                start_slash++;
                /* code */
            }
            
        }
        if(str[p] == '$' && str[p+1] != '/' && (start_slash == 0 || start_slash % 2 == 0))
        { 
            cpt = 1;
            p++;
            start = p;
            while(str[p] != '$' && str[p] != ' ' && str[p] != '\0' && str[p] != '\'' && str[p] != '"' && str[p] != '=')
                p++;
            ft_CheckVariables(ft_substr(str,start,p-start),env,&stock,&j);
        }
        else
        {
            
            stock[j] = str[p];
            j++;
            p++;
        }
    }
    //printf("st |%s|\n",stock);
        if(cpt == 1)
        {
            //printf("ret 0.5 |%s|  \n",stock);
            return stock;
        }
            
        else
        {
            //printf("ret 0 |%s|  \n",str);
            return str;
        }
            
        
    
}