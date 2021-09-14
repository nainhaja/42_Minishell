#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include "get_next_line.h"
#include <sys/wait.h>

void ft_stock_split(char *str, int *i,int cpt)
{
    while(str[*i])
    {
        if(str[*i] == '\'')
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
                break;
            }
               
        }
        if(str[*i] == '"')
        {
            *i = *i +1;
            while(str[*i] != '"' && str[*i] != '\0')
                *i = *i +1;
            if(str[*i] != '\0')
                *i = *i +1;
            else
            { 
                //printf("xD\n");
                split[cpt] = ft_substr(str,g_start,*i - g_start - 1);
                g_start = *i + 1;
                break;
            }
        }
        if(str[*i] == ';')
        {
            
            split[cpt] = ft_substr(str,g_start,*i - g_start);
            g_start = *i + 1;
            *i = *i +1;
            break;
        }
        *i = *i +1;
    }
}

void ft_remove_quotes_file(char *str,int *i)
{
    int start_sq=0;
    int start_dq=0;
    start_sq = *i;
    start_dq = *i;
    while(str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i])
    {
        if(str[*i] == '\'')
        {
            g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));
            start_sq = *i + 1;
            while (str[*i] != '\'' && str[*i] != '\0')
                *i = *i + 1;
            g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,start_sq,*i - start_sq));
            *i = *i + 1;
            g_red_start = *i;
        }
        else if(str[*i] == '"')
        {
            g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));
            start_dq = *i + 1;          
            while (str[*i] != '"' && str[*i] != '\0')
                *i = *i + 1;
            g_red_buff = ft_strjoin(g_red_buff,ft_substr(str,start_dq,*i - start_dq));
            *i = *i + 1;
            g_red_start = *i;
        }
        else
        {
            if(str[*i] != '\0')
                *i = *i + 1;
        }         
    }
    if (g_red_start != ft_strlen(str))
        g_red_buff  = ft_strjoin(g_red_buff,ft_substr(str,g_red_start,*i - g_red_start));  
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
            {
                ptr =ft_strjoin(ptr,ft_substr(str,start,i - start));
                i = i + 2;
                while(str[i] == ' ' && str[i])
                    i++;
                g_red_start = i;
                ft_remove_quotes_file(str,&i);
                g_fd = open(g_red_buff,O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0777);
                g_red_buff = ft_strdup("");
                dup2(g_fd,1);
                start = i;
            }
            if(str[i] == '>' && str[i+1] != '>')
            {
                ptr = ft_strjoin(ptr,ft_substr(str,start,i - start));
                i = i + 1;
                while(str[i] == ' ' && str[i])
                    i++;
                g_red_start = i;
                ft_remove_quotes_file(str,&i);
                g_fd = open(g_red_buff,O_TRUNC | O_WRONLY | O_CREAT,0777);
                g_red_buff = ft_strdup("");
                dup2(g_fd,1);
                start = i;
            }
        }
        if(str[i] == '<')
        {
            ptr =ft_strjoin(ptr,ft_substr(str,start,i - start));
            i = i + 2;
            while(str[i] == ' ' && str[i])
                i++;
            g_red_start = i;
            ft_remove_quotes_file(str,&i);
            g_fd = open(g_red_buff,O_RDONLY,0777);
            g_red_buff = ft_strdup("");
            start = i;
            dup2(g_fd,0);
            g_read = 1;
        }
        i = i + 1;
    }
    ptr = ft_strjoin(ptr,ft_substr(str,start,i - start));
    free(split[cpt]);
    split[cpt] = ft_strdup(ptr);
    return ptr;
}
int main(int argc,char **argv,char **env)
{
    char *haha;
    int i;
    int start = 0;
    g_fd = 1;
    copy(env,ft_strrlen(env));
     char *buff;
     char *ptr;
     int n= 0;
     int startt,j;
     //g_red = 0;
     g_start = 0;
     int awdi=0;
     int split_cpt=0;
     int stdio[2];
     char **export_tab;
     stdio[0] = dup(0);
     stdio[1] = dup(1);
     
    while(1)
    {
        
        g_null = 0;
        dup2(stdio[0], 0);
        dup2(stdio[1], 1);
         write(1,"$> ",3);
         
        get_next_line(0,&haha);
        i = 0;
        //printf("")
        if(haha[ft_strlen(haha) - 1] != ';')
            haha = ft_strjoin(haha,";");
        
        ft_check_split(haha);
        
        split = malloc(sizeof(char*)*(g_red));
       
        while (g_red > split_cpt)
        {
            ft_stock_split(haha,&awdi,split_cpt);
            split_cpt++;
        }
        
        split_cpt = 0;
        while(split_cpt < g_red)
        {
            g_read = 0;

            buff = ft_remove_quotes(ft_remove_spaces(ft_check_redr(split[split_cpt],split_cpt), &start, &i),env);
            startt = start;
            j = i;
            if(strcmp(buff,"echo") == 0)
            {
                if(strcmp(ft_remove_quotes(ft_remove_spaces(split[split_cpt], &startt, &j),env),"-n") == 0)
                    ft_putstr(ft_checkCases(ft_remove_n(split[split_cpt]+j),env));
                else
                {
                        int pid = fork();
                        if (pid == 0)
                        {
                            
                            //printf("without spaces and slash \n |%s|\n",ft_remove_slash(ft_remove_spacess(split[split_cpt],start,i)));
                            //exit(0);
                            ptr_dup = ft_remove_slash(ft_remove_quotes(ft_remove_spacess(split[split_cpt],start,i),env));
                            // ft_putstr(ptr_dup);
                            // write(1,"\n",1);
                            printf("Final |%s|\n",ptr_dup);
                            close(g_fd);
                            dup2(stdio[1], 1);
                            exit(0);
                        }
                        else if(pid > 0)
                            wait(NULL);
                }  
            } 
            else if(strcmp(buff,"env") == 0)
            {
                printlist(0);
            }
            else if(strcmp(buff,"export") == 0)
            {
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
            else if(strcmp(buff,"unset") == 0)
            {
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
            else
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
                // //parent kitsna child imot bach ikmel khdimto
            }
            i = 0;
            start = 0;
            split_cpt++;
        }
        start = 0;
        
        
        split_cpt = 0;
        while(split_cpt < g_red)
        {
            free(split[split_cpt]);
            split_cpt++;
        }
        //free(split[split_cpt]);
        //free(split);
        split_cpt = 0;
        g_red = 0;
        i = 0;
        awdi = 0;
        g_start = 0;
     //printf("%s\n",ft_checkDollar(ayoub,env));
    }
   
}


