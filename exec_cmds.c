#include "get_next_line.h"

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

void exec_echo(int *stdio, int split_cpt, int start, char **env, int i)
{
    int pid = fork();
    if (pid == 0)
    {
        ptr_dup = ft_remove_slash(ft_remove_quotes(ft_remove_spacess(split[split_cpt],start,i),env));
        printf("|%s|\n",ptr_dup);
        close(g_fd);
        dup2(stdio[1], 1);
        exit(0);
    }
    else if(pid > 0)
        wait(NULL);
}

void exec_export(int split_cpt)
{
    char **export_tab;

    export_tab = ft_split(split[split_cpt],' ');
    if(export_tab[1] == NULL)
    {
        printlist(1);
    }
    else
    {
        int tab=1;
        while(export_tab[tab] != 0)
        {
            if(export_tab[tab][0] == '=')
                printf("export: `%s': not a valid identifier\n",export_tab[tab]);
            else 
                AddNode(ft_BeforeEq_two(ft_remove_quotes_two(export_tab[tab])),ft_AfterEq_two(ft_remove_quotes_two(export_tab[tab])));
            tab++;
        }
    }
}

void exec_unset(int split_cpt)
{
    char **export_tab;

    export_tab = ft_split(split[split_cpt],' ');    
    if(export_tab[1] != NULL)
    {
        int tab = 1;
        while(export_tab[tab] != 0)
        {
            DeleteNode(export_tab[tab]);
            tab++;
        }   
    }
}

void exec_cmds(int *stdio, int split_cpt, char **env)
{
    int plus=0;
    int id=fork();
    if(id == 0)
    {
        close(g_fd);
        dup2(stdio[1], 1);
        char **argvv=ft_split(ft_checkCases(split[split_cpt],env),' ');
        char *envv[]={NULL};
        while(path2[plus])
        {
            execve(ft_strjoin(path2[plus],argvv[0]), argvv, envv);
            plus++;
        }
        exit(0);
    }
    wait(NULL);
}

void check_conditions(int split_cpt, int *stdio, int start, char **env, int i, char *buff)
{
    int j;
    int startt;

    j = i;
    startt = start;
    if(strcmp(buff,"echo") == 0)
    {
        if(strcmp(ft_remove_quotes(ft_remove_spaces(split[split_cpt], &startt, &j),env),"-n") == 0)
            ft_putstr(ft_checkCases(ft_remove_n(split[split_cpt]+(j)),env));
        else
            exec_echo(stdio, split_cpt, start, env, i);
    } 
    else if(strcmp(buff,"env") == 0)
    {
        printlist(0);
    }
    else if(strcmp(buff,"export") == 0)
    {
        exec_export(split_cpt);
    }
    else if(strcmp(buff,"unset") == 0)
    {
        exec_unset(split_cpt);
    }
    else
    {  
        exec_cmds(stdio, split_cpt, env);
    }
}

void ft_free(int split_cpt)
{
    split_cpt = 0;
    while(split_cpt < g_red)
    {
        free(split[split_cpt]);
        split_cpt++;
    }
}

void    ft_divide(char *buff, int *stdio, char **env)
{
    int split_cpt;
    int start;
    int i;

    start = 0;
    i = 0;
    split_cpt = 0;
    while(split_cpt < g_red)
    {
        g_read = 0;
        buff = ft_remove_quotes(ft_remove_spaces(ft_check_redr(split[split_cpt],split_cpt), &start, &i),env);
        check_conditions(split_cpt, stdio, start, env, i, buff);
        i = 0;
        start = 0;
        split_cpt++;
    }
    ft_free(split_cpt);
}

void    ft_init(int *split_cpt, int *i, int *awdi)
{
    *split_cpt = 0;
    g_red = 0;
    *i = 0;
    *awdi = 0;
    g_start = 0;
}
