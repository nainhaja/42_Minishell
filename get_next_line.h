/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:46:13 by nainhaja          #+#    #+#             */
/*   Updated: 2019/11/06 23:53:30 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
struct node {
        char* BeforeEq;
        char* AfterEq;
        struct node* next;
    };
typedef struct node node_t;
node_t *head;

char **split;
int g_start;
char *ptr_dup;
int g_fd;
char *g_red_buff;
int g_red_start;
int g_red;
char *path;
char **path2;
int g_null;
int g_read;
int	ft_strcmp(const char *str, const char *to_find);
char	**ft_split(char const *s, char c);
int		get_next_line(int fds, char **line);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, unsigned int start, unsigned int len);
char	*ft_strchr(char *str, int c);
size_t	ft_strlen(char *str);
int key_press(int key, void *ptr);
char		*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, unsigned int len);
char *ft_checkDollar(char *str,char **env);
char *ft_RmSpace(char *s,int c);
char *ft_AddSpace(char *s,int i);
char *ft_BeforeEq(char *k);
char *ft_AfterEq(char *k);
char			**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char *ft_BeforeEq_two(char *k);
char *ft_AfterEq_two(char *k);
char *ft_remove_quotes_two(char *buf);
int    ft_checkQuotes(int *i,int *cpt,int *cpt2,char *s);
void    ft_storeData(char *s,char **str,int start,int i,char **env);
char *ft_remove_spaces(char *haha, int *start, int *i);
void ft_get_between_spaces(char *haha,int *i,int *start,char **ptr);
void ft_get_between_slash(char *haha,int *i,int *start,char **ptr);
void ft_get_string_quotes(char *haha,int *i,int *start,char **ptr);
char *ft_remove_spacess(char *haha, int start, int i);
char *ft_remove_slash(char *haha);
char *ft_remove_quotes(char *buf, char **env);
void ft_sort();
char *ft_checkCases(char *s,char **env);
char    *ft_remove_n(char *str);
void copy(char **t,int n);
int get_listcount();
void exec_echo(int *stdio, int split_cpt, int start, char **env, int i);
void printlist(int x);
void DeleteNode( char *t);
int     search_lastRed(char *str);
int  search_used_node(char *beforeEq, char *AfterEq);
void AddNode(char *beforeEq, char *AfterEq);
char * SearchNode(char *t);
int ft_strrlen(char **v);
void ft_putstr(char *str);
void ft_check_split(char *str);
void exec_export(int split_cpt);
void exec_unset(int split_cpt);
void exec_cmds(int *stdio, int split_cpt, char **env);
void check_conditions(int split_cpt, int *stdio, int start, char **env, int i, char *buff);
void    ft_divide(char *buff, int *stdio, char **env);
char *ft_check_redr(char *str,int cpt);
void ft_free(int split_cpt);
void    ft_init(int *split_cpt, int *i, int *awdi);
void ft_stock_split(char *str, int *i,int cpt);
void ft_remove_quotes_file(char *str,int *i);

#endif