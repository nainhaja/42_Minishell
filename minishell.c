#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include "get_next_line.h"
#include <sys/wait.h>

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
    int startt;
    g_start = 0;
    int awdi=0;
    int split_cpt=0;
    int stdio[2];
    //  char **export_tab;
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
        if(haha[ft_strlen(haha) - 1] != ';')
            haha = ft_strjoin(haha,";");
        ft_check_split(haha);
        split = malloc(sizeof(char*)*(g_red));
        while (g_red > split_cpt)
        {
            ft_stock_split(haha,&awdi,split_cpt);
            split_cpt++;
        }
        ft_divide(buff, stdio, env);
        ft_init(&split_cpt, &i, &awdi);
     //printf("%s\n",ft_checkDollar(ayoub,env));
    }
   
}


