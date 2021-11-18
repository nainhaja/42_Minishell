# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 17:40:55 by nainhaja          #+#    #+#              #
#    Updated: 2021/11/09 17:40:58 by nainhaja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Wextra -Werror -lreadline -o minishell

LDFLAGS="-L/Users/nainhaja/.brew/opt/readline/lib"

CPPFLAGS="-I/Users/nainhaja/.brew/opt/readline/include"

SRC = file_red.c ft_split_spaces.c heredocs.c split_cmds.c\
check_parsing.c	ft_atoi.c ft_split_spaces_sec.c parsing.c\
split_cmds_pipes.c check_rest.c ft_isalpha.c ft_strcmp.c\
manage_node.c pipes.c utils.c check_variables.c	ft_isdigit.c\
manage_struct.c	pipes_sec.c	echo_n.c ft_itoa.c ft_substr.c manage_variables.c print_env.c\
execute.c ft_putchar_fd.c get_rest_cmd.c redirictions.c\
export_cases.c ft_putstr_fd.c heredoc.c minishell.c redirictions_pipes.c\
ft_split.c heredoc_sec.c rest.c maange_cases.c ft_strjoin.c ft_strstr.c\

NAME = minishell

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(LDFLAGS) $(CPPFLAGS)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all
