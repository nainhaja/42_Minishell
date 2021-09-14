#include "get_next_line.h"

int get_listcount()
{
    node_t *temp = head;
    int i = 0;
    while(temp!=NULL)
    {
        temp=temp->next;
        i++;
    }
    return i;
}


void printlist(int x) 
{
    node_t *temp = head;
    
    if(x == 1)
    {
        ft_sort();
        int i = 0;
        while(temp!=NULL)
        {
            
            printf("declare -x %s",temp->BeforeEq);
            if(temp->AfterEq == 0)
                printf("\n");
            else
                printf("=\"%s\" \n",temp->AfterEq);
            temp=temp->next;
            i++;
        }
    }
    else
    {
        while(temp!=NULL)
        {
            if(temp->AfterEq != 0)
            {  
                printf("%s=",temp->BeforeEq);
                printf("%s \n",temp->AfterEq);
            }
            temp=temp->next;
        }
    }
}

void DeleteNode( char *t)
{
    
    node_t *tempp = head;
    while(tempp->next !=NULL)
    {
        if(strcmp(tempp->next->BeforeEq,t) == 0)
        {
            node_t *next = tempp->next->next;
            tempp->next = next;
            break ;
        }
            
        tempp=tempp->next;
    }

}
int     search_lastRed(char *str)
{
    int i=0;
    int cpt=0;
    while(str[i])
    {
        if(str[i] == '>')
            cpt = i;
        i++;
    }
    return cpt;
}

int  search_used_node(char *beforeEq, char *AfterEq)
{
    char *afterEq;
    node_t *tempp = head;
    while(tempp->next !=NULL)
    {
        if(strcmp(tempp->next->BeforeEq,beforeEq) == 0 && AfterEq != 0)
        {
           tempp->next->AfterEq = AfterEq;
           return 1;
        }
        else if(strcmp(tempp->next->BeforeEq,beforeEq) == 0 && AfterEq == 0)
            return 1;
        tempp=tempp->next;
    }
    return 0;
}