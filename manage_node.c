#include "get_next_line.h"

void AddNode(char *beforeEq, char *AfterEq)
{
    node_t *temp =(node_t*) malloc(sizeof(node_t));
    node_t *tempp = head;
    
    if(search_used_node(beforeEq,AfterEq) == 0)
    {
        temp->BeforeEq = ft_strdup(beforeEq);
        if(AfterEq == 0)
            temp->AfterEq = NULL;
        else
            temp->AfterEq = ft_strdup(AfterEq);
        temp->next=NULL;
        while(tempp->next!=NULL)
        {
            tempp=tempp->next;
        }
        tempp->next = temp;
    }
}

char * SearchNode(char *t)
{
    char *afterEq;
    node_t *tempp = head;
    while(tempp->next !=NULL)
    {
        if(strcmp(tempp->next->BeforeEq,t) == 0)
        {
           return tempp->next->AfterEq;
        }
        tempp=tempp->next;
    }
    return 0;
}

int ft_strrlen(char **v)
{
    int i=0;
    while(v[i])
    {
        i++;
    }
    return i;
}
void ft_putstr(char *str)
{
    int i = 0;
    while(str[i])
    {
        write(1,&str[i],1);
        i++;
    }
}

void ft_check_split(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '\'')
        {
            i++;
            while(str[i] != '\'' && str[i] != '\0')
                i++;
            if(str[i] != '\0')
                i++;
            else
            {
                g_red++;
                break;
            }
                
        }
        if(str[i] == '"')
        {
            i++;
            while(str[i] != '"' && str[i] != '\0')
                i++;
            if(str[i] != '\0')
                i++;
            else
            {
                g_red++;
                break;
            }
        }
        if(str[i] == ';')
        {
            g_red++;
        }
        i++;
    }
}