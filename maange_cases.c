#include "get_next_line.h"

void ft_sort()
{
    node_t *temp = head;
    int sort_indice=1;
    char *tmp_be;
    char *tmp_ae;
    while (sort_indice)
    {
        sort_indice = 0;
        while (temp->next != NULL)
        {
            if(strcmp(temp->BeforeEq,temp->next->BeforeEq) > 0)
            {
                sort_indice = 1;
                tmp_be = temp->BeforeEq;
                temp->BeforeEq = temp->next->BeforeEq;
                temp->next->BeforeEq = tmp_be;

                tmp_ae = temp->AfterEq;
                temp->AfterEq = temp->next->AfterEq;
                temp->next->AfterEq = tmp_ae;
            }
            temp = temp->next;
        }
        temp = head;
    }
    
}
char *ft_checkCases(char *s,char **env)
{
    char *ret;
    char *plus;

    int length = strlen(s);
    ret = malloc(sizeof(char)*strlen(s));
    int i=0;
    int cpt = 0;
    int cpt2 = 0;
    int start = 0;
    int Fin=0,end=0;
    char *str;
    str = "";
    start = ft_checkQuotes(&i,&cpt,&cpt2,s);
    //printf("s = |%s|\n",s);
    while(s[i])
    {
        
        if((s[i] == '\'' && cpt == 1 ) || (s[i] == '"' && cpt2 == 1 ))
        {
            ft_storeData(s,&str,start,i,env);
            if(s[i+1] == ' ')
                str = ft_AddSpace(str,1);
            cpt = 0;
            end = i+1;
            cpt2 = 0;
            Fin = i+1;
        }
        else if(s[i] == '\'' && cpt == 0 && cpt2 == 0)
        {
            if(i != 0 && s[i-1] == ' ')
               str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),1));
            else
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),0));
            cpt = 1;
            start = i+1;
        }
        else if(s[i] == '"' && cpt2 == 0 && cpt == 0 )
        {   
            //printf("ret1 = |%s|\n",str);
            cpt2 = 1;
            start = i+1;
            if(i != 0 && s[i-1] == ' ')
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),1));
            else
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),0));
            //printf("ret2 = |%s|\n",str);
        }
        i++;
    }
    //printf("ret3 = |%s|\n",str);
    str = ft_strjoin(str,ft_checkDollar(ft_RmSpace(ft_substr(s,Fin,i-Fin),2),env));
    
    ret = str;
    
    return ret;
}
char    *ft_remove_n(char *str)
{
    int i;
    char *ptr;
    int start;
    int ft_break;

    i = 0;
    start = 0;
    ft_break = 0;
    ptr = ft_strdup("");
    while(str[i])
    {
        while(str[i] == '-' && str[i + 1] == 'n')
        {
            ptr = ft_strjoin(ptr, ft_substr(str, start, i - start));
            i++;
            while (str[i] == 'n' && str[i])
                i++;

            while (str[i] == ' ' && str[i])
            {
                i++;
            }
            start = i;
            ft_break = 1;
        }
        if(ft_break == 1)
        {
            ptr = ft_strjoin(ptr, ft_substr(str, start, ft_strlen(str) - start));
            break;
        }
        i++;
    }
    if(start != i)
    {
        ptr = ft_strjoin(ptr, ft_substr(str, start, i - start));
    }
    //printf("%s\n",ptr);
    return ptr;
}

void copy(char **t,int n)                        
{
    node_t *temp = malloc(sizeof(node_t));
    temp->BeforeEq= ft_BeforeEq(t[0]);
    temp->AfterEq = ft_AfterEq(t[0]);
    temp->next=NULL;
    head = temp;
    int i=1;
    while(i<n)
    {
        node_t *temp2= malloc(sizeof(node_t));
        temp->next= temp2;
        temp2->BeforeEq= ft_BeforeEq(t[i]);
        temp2->AfterEq = ft_AfterEq(t[i]);
        temp2->next = NULL;
        temp=temp2;
        i++;
     }  
}