#include "get_next_line.h"

void ft_get_string_quotes(char *haha,int *i,int *start,char **ptr)
{
    int end;

    char c = haha[*i];
    *i = *i + 1;
    while(haha[*i] != c && haha[*i])
        *i = *i + 1;     
    if(haha[*i] != '\0')
    {
        *i = *i + 1;
        while(haha[*i] != ' ' && haha[*i] != '\'' && haha[*i] != '"' && haha[*i] != '\0')
            *i = *i + 1;
    }
    end = *i;
    *ptr = ft_strjoin(*ptr, ft_substr(haha,*start,end - *start));
    while(haha[*i] == ' ' && haha[*i] != '\'' && haha[*i] != '"' && haha[*i] != '\0')
        *i = *i + 1;
    if(haha[*i] != '\0')
        *ptr = ft_strjoin(*ptr," ");
    *start = *i;
}

char *ft_remove_spacess(char *haha, int start, int i)
{
    char *ptr;
    int end;
    ptr = ft_strdup("");
    while(haha[i])
    {
        if(haha[i] == '\'')
        {
            if(haha[i - 1]  == '\\')
            {
                ptr = ft_strjoin(ptr,"' ");
                // 
                start = i;
                i++;
                //
            }  
            else 
                ft_get_string_quotes(haha,&i,&start,&ptr);
        }
            
        else if(haha[i] == '"')
            ft_get_string_quotes(haha,&i,&start,&ptr);
        else if(haha[i] == ' ')
        {
            while(haha[i] == ' ' && haha[i] != '\0')
                i++;
            if(haha[i] == '\0')
                return ptr;
            else
            {
                start = i;
                ft_get_between_spaces(haha,&i,&start,&ptr);
            }
        }
        else
        {
            start = i;
            ft_get_between_spaces(haha,&i,&start,&ptr);
        } 
    }
    if(haha[start] != '\0')
        ptr = ft_strjoin(ptr, ft_substr(haha,start,end - start));
    printf("ptr |%s|\n",ptr);
    return ptr;
}

char *ft_remove_slash(char *haha)
{
    char *ptr;
    int start;
    int i = 0;
    int end;
    int start_slash = 0;
    ptr = ft_strdup("");
    
    //printf("haha |%s| \n",haha);
    while(haha[i])
    {
        if(haha[i] == '\'')
            ft_get_string_quotes(haha,&i,&start,&ptr);
        else if(haha[i] == '"')
            ft_get_string_quotes(haha,&i,&start,&ptr);
        else if(haha[i] == '\\')
        {
            //printf("dkhlat\n");
            while(haha[i] == '\\' && haha[i] != '\0')
            {
                start_slash++;
                i++;
            }
            if(haha[i] == '\0')
                return ptr;
            else
            {
                start = i;
                if(start_slash > 1)
                {
                    int x = 0;
                    while(x < start_slash / 2)
                    {
                        ptr = ft_strjoin(ptr,"\\");
                        x++;
                    }
                    
                }
                if ((start_slash % 2) != 0 && haha[i] == ' ' && start_slash != 0)
                        ptr = ft_strjoin(ptr," ");
                //printf("sladh num %s\n ",haha+i);
                start_slash = 0;
                ft_get_between_slash(haha,&i,&start,&ptr);
            }
        }
        else
        {
                            //printf("sladh num %d\n ",start_slash);

            start = i;
            ft_get_between_slash(haha,&i,&start,&ptr);
        } 
    }
    if(haha[start] != '\0')
        ptr = ft_strjoin(ptr, ft_substr(haha,start,end - start));
    return ptr;
}

char *ft_remove_quotes(char *buf, char **env)
{
    int i = 0;
    int cpt = 0;
    int startquotes,endquotes;
    int start_dquotes,end_dquotes;
    int start = 0,end;
    char *ptr = ft_strdup("");
    
    //printf("buff %s\n",buf);
    while(buf[i])
    {

        if(buf[i] == '\'')
        {
            //printf("ha wahd lah\n");
            if(i != 0 && buf[i - 1] == '\\')
            {
                //ptr = ft_strjoin(ptr, (ft_substr(buf,i,i)));
                //start = i + 1;
                i++;
                
            }
            else
            {
                if(cpt == 0)
                {
                    cpt = 1;
                    startquotes = i + 1;
                    ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i - start),env));
                }
                else if(cpt == 1)
                {
                    start = i + 1;
                    endquotes = i;
                    cpt = 0;
                    ptr = ft_strjoin(ptr, ft_substr(buf,startquotes,endquotes - startquotes));
                }
            }
        }
        else if(buf[i] == '"')
        {

            //printf("|%s|\n",ptr);
            if(i != 0 && buf[i - 1] == '\\')
            {
                // ptr = ft_strjoin(ptr, (ft_substr(buf,i,i)));
                // start = i + 1;
                i++;
                //printf("kk\n");
                // ç
                // exit(0);
            }
            else
            {
                if(cpt == 0)
                {

                    cpt = 2;
                    start_dquotes = i + 1;
                    //printf("tr %s\n",ptr);
                    ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i - start),env));
                    //printf("dipasa |%c| |\n",buf[start]);
                }
                else if(cpt == 2)
                {
                    //printf("kkk\n");
                    start = i + 1;
                    end_dquotes = i;
                    cpt = 0; 
                    ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start_dquotes,end_dquotes - start_dquotes),env));
                    //printf("ok |%s|\n",ptr); 
                }
            }
        }
        i++;
    }
    if (buf[start] != '\0')
        ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i),env));
    //printf("Ptr new |%s|\n",ptr);
    return ptr;
}